# ScorpioLog

A simple wrapper around `spdlog` library. Supports logging to console in different colors and writing log files.

## Instalation

```
./scripts/installdep.sh
./scripts/buildall.sh
```

## Linking 

```
target_link_libraries(scorpio_log)
```

## Turn logging ON and OFF

### With CMake
To enable loggging, in `CMakeList.txt` file add the following line
```
add_compile_definitions(SCORPIO_LOG)
```
### Source code
To initialize library add the following lines at the beggining of your `main`. They can be used at the same time or each one of them separately.
```
LOGGER_INIT_CONSOLE;
LOGGER_INIT_FILE;
```
## Logging to files

Library backups each log to `logs_backup` folder. Logs from previous run of your programm are stored in `logs` folder.

## Examples

### Simple program
```
#include <scorpio_log/ScorpioLog.hpp>

int main()
{
    LOGGER_INIT_CONSOLE;
    LOGGER_INIT_FILE;

    LOGGER_TRACE("White string");
    LOGGER_INFO("{}", "Green string");
    LOGGER_WARN("{1} {0}", "string", "Yello");
    LOGGER_ERROR("Red string {}", 1);
    LOGGER_CRITICAL("Critical error");
}

```
### In this example noting gets printed to the console
```
#include <scorpio_log/ScorpioLog.hpp>

int main()
{
    LOGGER_TRACE("White string");
    LOGGER_INFO("{}", "Green string");
    LOGGER_WARN("{1} {0}", "string", "Yello");
    LOGGER_ERROR("Red string {}", 1);
    LOGGER_CRITICAL("Critical error");
}
```