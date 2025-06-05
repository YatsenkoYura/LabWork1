//Yuriy Yatsenko 135624@student.spbu.ru
//hello world project


#ifndef IMAGE_OPERATIONS_H
#define IMAGE_OPERATIONS_H

#include "ImageData.h"

/**
 * @class ImageOperations
 * @brief Статический класс с методами обработки BMP-картинок.
 */
class ImageOperations {
public:
    /**
     * @brief Поворачивает изображение на 90° по часовой стрелке.
     * @param src исходное изображение
     * @return новое изображение, повернутое по часовой стрелке
     */
    static ImageData rotateClockwise(const ImageData& src);

    /**
     * @brief Поворачивает изображение на 90° против часовой стрелки.
     * @param src исходное изображение
     * @return новое изображение, повернутое против часовой стрелки
     */
    static ImageData rotateCounterClockwise(const ImageData& src);

    /**
     * @brief Применяет гауссов блюр к изображению на месте.
     * @param img изображение, к которому будет применён фильтр
     */
    static void applyGaussianBlur(ImageData& img);
};

#endif // IMAGE_OPERATIONS_H