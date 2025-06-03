#ifndef IMAGEDATA_H
#define IMAGEDATA_H

#include <cstdint>

#pragma pack(push, 1)

/**
 * @struct Pixel
 * @brief Представление единственного пикселя в BMP (BGR + зарезервированный байт).
 */
struct Pixel {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t reserved;
};

/**
 * @struct FileHeader
 * @brief Заголовок BMP-файла (14 байт).
 *
 * Содержит сигнатуру «BM», общий размер файла, смещение до растровых данных.
 */
struct FileHeader {
    uint16_t typeID;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
};

/**
 * @struct InfoHeader
 * @brief Информационный заголовок BMP (обычно 40 байт – BITMAPINFOHEADER).
 *
 * Содержит размеры изображения, глубину цвета, формат сжатия и др.
 */
struct InfoHeader {
    uint32_t headerSize;
    int32_t  width;
    int32_t  height;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t imageSize;
    int32_t  xPixelsPerMeter;
    int32_t  yPixelsPerMeter;
    uint32_t colorsUsed;
    uint32_t importantColors;
};

#pragma pack(pop)

/**
 * @class ImageData
 * @brief Класс-обёртка для загрузки, хранения и сохранения BMP-изображения.
 *
 * Содержит заголовки FileHeader и InfoHeader, а также массив пикселей.
 */
class ImageData {
public:
    InfoHeader  infoHdr;
    FileHeader  fileHdr;
    Pixel     **pixels;

    /**
     * @brief Конструктор по умолчанию.
     *
     * Инициализирует указатель pixels в nullptr,
     * поля заголовков – нулями.
     */
    ImageData();

    /**
     * @brief Деструктор.
     *
     * Освобождает память пикселей, если она была выделена.
     */
    ~ImageData();

    /**
     * @brief Загрузить BMP-изображение из файла.
     * @param path Путь к файлу (C-строка).
     * @return true при успешной загрузке, false при ошибке открытия
     *         или несоответствии формата.
     *
     * Выделяет память под пиксели, заполняет fileHdr, infoHdr и pixels[].
     */
    bool loadFromFile(const char* path);

    /**
     * @brief Сохранить текущее изображение в BMP-файл.
     * @param path Путь для сохранения (C-строка).
     * @return true при успешной записи, false при ошибке.
     */
    bool writeToFile(const char* path) const;

    /**
     * @brief Освободить выделенную память под пиксели.
     *
     * Если pixels не равен nullptr, удаляет каждую строку и сам массив указателей.
     * После вызова pixels устанавливается в nullptr.
     */
    void freeMemory();
};

#endif // IMAGEDATA_H