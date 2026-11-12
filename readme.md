# okular system
библиотека для определения окружения систем
# настройка 
```sh
bazel run //:clangd # настройка clangd
bazel build //:library # сборка библиотеки liblibrary.so
bazel clean --expunge # отчистка сборки
bazel run //:module # компиляция и запуск бинарника модуля
```
