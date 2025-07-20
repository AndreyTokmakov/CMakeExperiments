https://cmake.org/cmake/help/latest/module/FetchContent.html

========================================================================================================
                        Options
========================================================================================================

FetchContent_Declare(<name>
    GIT_REPOSITORY <url>
    GIT_TAG        <commit/branch/tag>
    GIT_SHALLOW    <BOOL>
    GIT_PROGRESS   <BOOL>
    GIT_SUBMODULES ""
    GIT_SUBMODULES_RECURSE <BOOL>
    GIT_REMOTE_NAME <remote>
    GIT_CONFIG     <key1> <val1> <key2> <val2> ...
    GIT_CLONE_OPTIONS <args>...

    SVN_REPOSITORY <url>
    SVN_REVISION   <rev>

    URL            <url or file>
    URL_HASH       <algo>=<hash>
    DOWNLOAD_NAME  <filename>
    DOWNLOAD_DIR   <dir>

    SOURCE_DIR     <local-path>
    BINARY_DIR     <build-path>

    PATCH_COMMAND  <cmd>...
    CONFIGURE_COMMAND <cmd>...
    BUILD_COMMAND     <cmd>...
    INSTALL_COMMAND   <cmd>...
    TEST_COMMAND      <cmd>...

    LOG_DOWNLOAD  <BOOL>
)


========================================================================================================

URL	                    Прямая ссылка на архив (.zip/.tar.gz)
URL_HASH	            Контрольная сумма (например, SHA256=...)
SOURCE_DIR	            Указание на локальную папку, если есть
DOWNLOAD_DIR	        Куда сохранять загруженные архивы
GIT_SUBMODULES	        Какие submodules включать
GIT_SUBMODULES_RECURSE	Рекурсивная загрузка всех submodules
GIT_PROGRESS	        Показывать прогресс git clone
GIT_REMOTE_NAME	        Имя remote (по умолчанию origin)
GIT_CONFIG	            Конфигурация git-параметров
GIT_CLONE_OPTIONS	    Передаётся в git clone (например, --single-branch)
PATCH_COMMAND	        Команда патча исходников
CONFIGURE_COMMAND	    Своя команда конфигурации (по умолчанию CMake)
BUILD_COMMAND	        Своя команда сборки
INSTALL_COMMAND	        Своё make install
TEST_COMMAND	        Свои тесты (обычно ctest)
LOG_DOWNLOAD	        TRUE = логировать загрузку (по умолчанию OFF)
DOWNLOAD_NAME	        Переименование загружаемого архива


FetchContent_Declare(
      mylib
      GIT_REPOSITORY https://github.com/user/mylib.git
      GIT_TAG        v1.2.3
      GIT_SHALLOW    TRUE
      GIT_PROGRESS   TRUE
      GIT_CONFIG     advice.detachedHead false core.autocrlf input
      GIT_CLONE_OPTIONS --single-branch

      PATCH_COMMAND  patch -p1 < ${CMAKE_SOURCE_DIR}/fix.patch
      CONFIGURE_COMMAND ""
      BUILD_COMMAND ""
      INSTALL_COMMAND ""
)


========================================================================================================

FetchContent_Declare(<NAME>
    .......
    GIT_PROGRESS ON
)


Указывает, что нужно получать информацию о прогрессе загрузки.
Это может быть полезно, если нужно видеть, как FetchContent извлекает зависимости, во время настройки проекта

- Клонируется только один коммит (тот, что соответствует GIT_TAG)
- Эквивалентно git clone --depth 1
- Уменьшает размер загрузки, особенно полезно в CI
- Работает быстрее (особенно для больших репозиториев)

- Нельзя использовать вместе с GIT_TAG = master и делать GIT_SUBMODULES_RECURSE TRUE, если submodules указывают на старые коммиты


Пример выгоды

    Допустим, у тебя fmt или protobuf, где репозиторий может быть 100–500 МБ.
        Без GIT_SHALLOW: клонируется вся история (включая ветки, теги, тысячи коммитов)
        С GIT_SHALLOW TRUE: клонируется только нужный коммит
        Сборка в CI может ускориться на 10–60 секунд в зависимости от сети и кэша.

 Когда НЕ стоит использовать:

    Когда нужен доступ к подмодулям, которые сами требуют древнюю историю
    Когда делаешь сборку на ветке, и тебе важны коммиты до текущего (например, HEAD~1)
    Когда хочешь использовать GIT_SUBMODULES_RECURSE TRUE + GIT_TAG не на HEAD


========================================================================================================

Указывает, что нужно скачивать только нужный коммит из репозитория Git.
Это может быть полезно, если нужно загрузить только определённую ветвь зависимости, распределённую по отдельным ветвям.
По умолчанию FetchContent вызывает выборку всех существующих ветвей, что может привести к загрузке избыточных данных.


FetchContent_Declare(<NAME>
    .......
    GIT_SHALLOW ON
)


========================================================================================================