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
(Пример нуждается в обновлении!)

### Добавление своих свойств
Свойства - это ключи в map `properties` из класса Plugin. Поскольку ключи должны быть строго определенных типов,
в качестве них используется особый тип - `PluginAPI::TYPE::Type`. На самом деле, `TYPE` - это пространство имен, 
что позволяет вам расширять набор свойств, дописав в коде своего плагина следующую конструкцию:

```
namespace PluginAPI {
namespace TYPE {
    constexpr Type MY_FANCY_TYPE = Type(COUNT);
    constexpr Type ANOTHER_TYPE = Type(COUNT + 1);
};
};
```
### Сборка разделяемой библиотеки
Для локальных тестов можно собирать плагин следующим образом:
```
gcc -c -fPIC MyFancyPlugin.cpp
gcc MyFancyPlugin.o -shared -o MyFancyPlugin.so
```
В репозитории настроен CI, поэтому для загрузки скрипта вам достаточно положить исходники вашего файла в папку pending и через некоторое время он будет автоматически собран и появится в папке plugins. Важно отметить, что в именах исходников не должно быть пробельных символов, равно как и в имени плагина. Также, все файлы должны разложены строго как указано далее.



## Взаимодействие плагина с глобальными параметрами хоста

Плагин имеет возможность менять текущие основной и фоновый цвета, установленные в программе. Для того, чтобы сделать это, необходимо и достаточно сохранить текущее значение в соответствующее поле `properties`. На хост-программу возлагается обязанность проверять поля `properties` после каждого вызова `stop_apply` и обновлять настройки хоста соответствующим образом.


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

## Доступные плагины
#### ColorFilter by fckxorg
Простой плагин цветового филтра, не требует дополнительных элементов управления, 
в качестве свойств принимает только цвет, выбранный на палитре.

#### BoxBlur by BorisTab
Плагин простого размытия холста. Не требует дополнительных элементов управления.
В качестве размера ядра свертки принимает thickness. 

#### GaussianBlur by fckxorg
Плагин размытия по Гауссу. Принимает параметр <img src="https://render.githubusercontent.com/render/math?math=\sigma"> для распределения,
радиус размытия и флаг дублирования границ изображения. Требует поддержки создания собственных элементов управления.
