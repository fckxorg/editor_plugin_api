# Editor Plugin API

## Порядок написания плагина

* отнаследоваться от `PluginAPI::Plugin`, переопределить все методы
* определить функцию `get_plugin()` следующим образом
```c
extern "C" PluginAPI::Plugin* get_plugin() {
  return PluginAPI::get_instance<ВАШ ТИП ПЛАГИНА>();
}
```

Для референса можно и нужно использовать [Пример](./example)


## Структура поставки плагина

```
pending
|_MyPlugin
| |_src             -
| | |_MyPlugin.hpp  |--- исходники, из которых нужно собрать плагин
| | |_MyPlugin.cpp  -     
| |_icon.xxx        ---- иконка для отрисовки в панели инструментов
| |_PLUGIN_INFO     ---- информация для отображения где-нибудь ( ͡° ͜ʖ ͡°)
```

## Структура распространения плагина

Мы скомпируем под необходимые платформы:
```
plugins
|_MyPlugin
| |_MyPlugin.so
| |_MyPlugin.dll
| |_MyPlugin.abracadabra
| |_icon.xxx
| |_PLUGIN_INFO
```
