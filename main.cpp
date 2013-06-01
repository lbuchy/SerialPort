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

#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include <serialport.h>

#include <string>

using namespace std;

void readHandler(
        boost::array<char,SerialPort::k_readBufferSize> const& buffer,
        size_t bytesTransferred)
{
    std::string data;
    std::copy(buffer.begin(), buffer.begin()+bytesTransferred, std::back_inserter(data));
    std::cout << data;
}

int main()
{
    boost::asio::io_service ioSrv;

    SerialPort serialPort(ioSrv, 115200, "/dev/pts/1");

    serialPort.DataRead.connect(&readHandler);

    boost::thread t(
                boost::bind(
                    &boost::asio::io_service::run,
                    &ioSrv));

    if(serialPort.Initialize())
    {
        std::cerr << "Initialization failed!" << std::endl;
        return 1;
    }

    std::string msg = "hello cookie\n";

    for(int i = 5; i; --i)
    {
        serialPort.Write(msg);
        sleep(1);
    }


    serialPort.Close();
    ioSrv.stop();
    t.join();

    return 0;
}

