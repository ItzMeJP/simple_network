# Simple Network API

<a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-nd/4.0/88x31.png" />

* [Description](#Description)
* [Examples](#Example)
* [Installation](#Installation)
* [TODO](#Todo)

## <a name="Description"></a>1. Description

The API is a simple usage API that implements UDP and TCPs protocol. The usage is motivated by applications that just need to exchange data without a lot of restrictions . The Simple Network API is a wrapper package of [Boos::asio](https://www.boost.org/doc/libs/1_75_0/doc/html/boost_asio.html) library.

## <a name="Example"></a>2. Examples

The examples codes can be found [here](./src/examples). Detailed descriptions of each method and functions can be found commented in [headers files](./include/simple_network)

## <a name="Installation"></a>3. Examples
```
mkdir build
cd build
cmake ..
make install
```

After the installation the shared libs will be located at ```/usr/local/lib/simple_network```. The headers files will be located at ```/usr/local/include/simple_network```

## <a name="TODO"></a>4. TODO
- TCP server and client implementation.
