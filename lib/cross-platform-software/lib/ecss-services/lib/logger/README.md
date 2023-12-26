# Logger

If you use this as a standalone, you'll need [ETL](https://github.com/ETLCPP/etl).
You can add it with conan, or as a submodule, etc.

Don't forget to include the line `add_compile_definitions<LOG_LEVEL>` in your `CmakeLists.txt`, for example `add_compile_definitions(LOGLEVEL_TRACE)`.
