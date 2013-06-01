/*
Copyright (C) 2013  Logan Buchy

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <vector>
#include <deque>


class SerialPort
        : public boost::enable_shared_from_this<SerialPort>
{
public:
    static uint32_t const k_readBufferSize = 1024;

    typedef boost::shared_ptr<std::vector<char> > SharedBufferPtr_t;

    SerialPort(
            boost::asio::io_service &rIoService,
            uint32_t baud,
            std::string const& device);

    ~SerialPort();

    int Initialize();
    void Close();

    void Write(std::string const& msg);

    boost::signal<void (boost::array<char,k_readBufferSize> const&, size_t bytesTransferred)> DataRead;

private:
    void BeginRead_();
    void EndRead_(boost::system::error_code const& error, size_t bytesTransferred);

    void DoWrite_(SharedBufferPtr_t pBuffer);
    void BeginWrite_();
    void EndWrite_(boost::system::error_code const& error, size_t bytes_transferred);

    void DoClose_(boost::system::error_code const& error);

    bool m_bInitialized;
    boost::asio::io_service& m_rIoService;
    boost::asio::serial_port m_serialPort;
    boost::array<char,k_readBufferSize> m_rdBuf;
    std::deque<SharedBufferPtr_t> m_wrBuf;

    uint32_t m_bytesTransferred;
};

#endif // SERIALPORT_H
