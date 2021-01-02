/*  Serial Connection for POSIX
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 */

#ifndef PokemonAutomation_SerialConnectionPOSIX_H
#define PokemonAutomation_SerialConnectionPOSIX_H

#include <string>
#include <atomic>
#include <thread>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include "StreamInterface.h"

//#include <iostream>

namespace PokemonAutomation{

class SerialConnection : public StreamConnection{
public:
    //  UTF-8
    SerialConnection(const std::string& name, uint32_t baud_rate)
        : m_exit(false)
    {
        speed_t baud = B9600;
        switch (baud_rate){
        case 9600:  baud = B9600;   break;
        case 19200: baud = B19200;  break;
        case 38400: baud = B38400;  break;
        case 57600: baud = B57600;  break;
        case 115200: baud = B115200;break;
        default:
            throw "Unsupported Baud Rate: " + std::to_string(baud_rate);
        }
//        std::cout << "desired baud = " << baud << std::endl;

        m_fd = open(name.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
        if (m_fd == -1){
            int error = errno;
            std::string str = "Unable to open serial connection. Error = " + std::to_string(error);
            if (error == EACCES){
                str += " (permission denied)\nPlease run as sudo.";
            }
            throw str;
        }

        struct termios options;
        if (tcgetattr(m_fd, &options) == -1){
            int error = errno;
            throw "tcgetattr() failed. Error = " + std::to_string(error);
        }
//        std::cout << "read baud = " << cfgetispeed(&options) << std::endl;
//        std::cout << "write baud = " << cfgetospeed(&options) << std::endl;

        //  Baud Rate
        if (cfsetispeed(&options, baud) == -1){
            int error = errno;
            throw "cfsetispeed() failed. Error = " + std::to_string(error);
        }
        if (cfsetospeed(&options, baud) == -1){
            int error = errno;
            throw "cfsetospeed() failed. Error = " + std::to_string(error);
        }
//        std::cout << "write baud = " << cfgetispeed(&options) << std::endl;
//        std::cout << "write baud = " << cfgetospeed(&options) << std::endl;

#if 0
        std::cout << "BRKINT  = " << (options.c_iflag & BRKINT) << std::endl;
        std::cout << "ICRNL   = " << (options.c_iflag & ICRNL) << std::endl;
        std::cout << "IMAXBEL = " << (options.c_iflag & IMAXBEL) << std::endl;
        std::cout << "OPOST   = " << (options.c_oflag & OPOST) << std::endl;
        std::cout << "ONLCR   = " << (options.c_oflag & ONLCR) << std::endl;
        std::cout << "ISIG    = " << (options.c_lflag & ISIG) << std::endl;
        std::cout << "ICANON  = " << (options.c_lflag & ICANON) << std::endl;
        std::cout << "ECHO    = " << (options.c_lflag & ECHO) << std::endl;
        std::cout << "ECHOE   = " << (options.c_lflag & ECHOE) << std::endl;
#endif
#if 1
        //  8 bits, no parity, 1 stop bit
        options.c_cflag &= ~PARENB;
        options.c_cflag &= ~CSTOPB;
        options.c_cflag &= ~CSIZE;
        options.c_cflag |= CS8;
#endif
#if 1
        //  Override all of Linux's stupid text defaults.
        options.c_iflag &= ~BRKINT;
        options.c_iflag &= ~ICRNL;
        options.c_iflag &= ~(IXON | IXOFF);
        options.c_iflag &= ~IMAXBEL;
        options.c_oflag &= ~OPOST;
        options.c_oflag &= ~ONLCR;
        options.c_lflag &= ~ISIG;
        options.c_lflag &= ~ICANON;
        options.c_lflag &= ~ECHO;
        options.c_lflag &= ~ECHOE;
#endif

        if (tcsetattr(m_fd, TCSANOW, &options) == -1){
            int error = errno;
            throw "tcsetattr() failed. Error = " + std::to_string(error);
        }

        if (tcgetattr(m_fd, &options) == -1){
            int error = errno;
            throw "tcgetattr() failed. Error = " + std::to_string(error);
        }
        if (cfgetispeed(&options) != baud){
//            std::cout << "actual baud = " << cfgetispeed(&options) << std::endl;
            throw "Unable to set input baud rate.";
        }
        if (cfgetospeed(&options) != baud){
//            std::cout << "actual baud = " << cfgetospeed(&options) << std::endl;
            throw "Unable to set output baud rate.";
        }

        //  Start receiver thread.
        try{
            m_listener = std::thread(&SerialConnection::recv_loop, this);
        }catch (...){
            close(m_fd);
        }
    }

    ~SerialConnection(){
        if (!m_exit.load(std::memory_order_acquire)){
            stop();
        }
    }

    virtual void stop() final{
        m_exit.store(true, std::memory_order_release);
        close(m_fd);
        m_listener.join();
    }

private:
    virtual void send(const void* data, size_t bytes){
        std::lock_guard<std::mutex> lg(m_send_lock);
        bytes = write(m_fd, data, bytes);
    }

    void recv_loop(){
        char buffer[32];
        while (!m_exit.load(std::memory_order_acquire)){
            int actual = read(m_fd, buffer, sizeof(buffer));
            if (actual > 0){
                on_recv(buffer, actual);
            }
        }
    }
    


private:
    int m_fd;
    std::atomic<bool> m_exit;
    std::mutex m_send_lock;
    std::thread m_listener;
};


}

#endif
