# Отчёт по производительности (с и без распараллеливания)

## Окружение тестирования
- ОС: Ubuntu (внутри WSL2 на Windows 10/11)
- Ядро Linux: стандартное WSL2 (версия ~5.x)
- Компилятор: g++ 9.3.0 (Ubuntu 20.04)
- Флаги компиляции: `-O2 -march=native -pthread`
- Виртуализация: Hyper-V / WSL2
- ОЗУ: 9 GiB DDR4
- CPU: AMD Ryzen 5 2600 Six-Core Processor

---

## Тестовый скрипт
Скрипт для измерения времени работы «с» и «без» распараллеливания:  
https://pastebin.com/dMdgEEUh

---

## Результаты
- Без распараллеливания: https://pastebin.com/14v4wKvU
- С распараллеливанием:   https://pastebin.com/b729X0xC

**Среднее время**
- Без многопоточности: ~0.142 s
- В многопоточном варианте: ~0.082 s

> Разница очевидна: распараллеливание ускоряет обработку почти в 2×.

---
## Входное изображение

| Параметр       | Значение            |
| -------------- | ------------------- |
| Имя файла      | input.bmp           |
| Путь           | test_file/input.bmp |
| Формат         | BMP (не сжатый)     |
| Размер файла   | 768 KB              |
| Разрешение     | 512 × 512 px        |
| Глубина цвета  | 24 bpp (RGB по 8)   |


![Input image](test_file/input.bmp "test_file/input.bmp")


## Подход к распараллеливанию
В реализации используется стандартная библиотека C++ `<thread>`.  
Функции обработки изображения (поворот по часовой, поворот против часовой, гауссово размытие) выполняются в трёх отдельных потоках одновременно.

Пример фрагмента из `main.cpp`:

```cpp
// создаём три потока — каждый свою операцию над копией исходного изображения
std::thread t1([&orig]() {
    auto cw = ImageOperations::rotateClockwise(orig);
    cw.writeToFile("output1.bmp");
    cw.freeMemory();
});

std::thread t2([&orig]() {
    auto ccw = ImageOperations::rotateCounterClockwise(orig);
    ccw.writeToFile("output2.bmp");
    ccw.freeMemory();
});

std::thread t3([&orig]() {
    // делаем неглубокую копию пикселей и размываем
    ImageData blur = orig;
    // … (копирование пикселей)
    ImageOperations::applyGaussianBlur(blur);
    blur.writeToFile("output3.bmp");
    blur.freeMemory();
});

// дожидаемся завершения всех потоков
t1.join();
t2.join();
t3.join();