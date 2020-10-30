# ScorpioLog

Prosty singleton wokół spdlog. Sugeruję korzystać z makrosów, łatwo wtedy wyłączyć logowanie w finalnej wersji projektu. Logger obsługuje kolorki, potrafi też zapisywać logi do pliku.

## Instalacja

```
./scripts/installdep.sh
./scripts/build.sh
./scripts/install.sh
```
Oczywiście nie zapomnij o `sudo`.

## Włączanie i wyłączanie logowania

- ### Z poziomu CMake
Jeżeli chcesz włączyć makra, w pliku `CMakeList.txt` swojego pliku dodaj tę linijkę
```
add_compile_definitions(SCORPIO_LOG)
```
- ### W kodzie źródłowym
Aby metody logujące działały, na początku maina należy umieścić oba albo wybrane makra
```
LOGGER_INIT_CONSOLE;
LOGGER_INIT_FILE;
```
Pierwsze z nich włącza logowanie do konsoli. Kolejna włącza lgowanie do pliku. Oba tryby mogą działać równocześnie.

## Przykłady użycia

- ### Prosty program
```
#include <scorpio_log/ScorpioLog.hpp>

int main()
{
    LOGGER_INIT_CONSOLE;
    LOGGER_INIT_FILE;

    LOGGER_TRACE("Ten napis będzie biały");
    LOGGER_INFO("{}", "Zielony napis");
    LOGGER_WARN("{1} {0}", "napis", "Żółty");
    LOGGER_ERROR("Czerwony napis {}", 1);
    LOGGER_CRITICAL("Krytyczny error");
}

```
- ### W tym natomiast nic nie zostanie wypisane do pliku ani do konsoli
```
#include <scorpio_log/ScorpioLog.hpp>

int main()
{
    LOGGER_TRACE("Ten napis będzie biały");
    LOGGER_INFO("{}", "Zielony napis");
    LOGGER_WARN("{1} {0}", "napis", "Żółty");
    LOGGER_ERROR("Czerwony napis {}", 1);
    LOGGER_CRITICAL("Krytyczny error");
}
```