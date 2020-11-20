#include "BrushFactory.hpp"
#include "Brush.hpp"
#include "Pen.hpp"

/**
 *
 * @param type type of drawing tools user wants to create
 *        1.Brush
 *        2.Pen
 * @return different drawing instance
 */

GeneralBrush * BrushFactory::createBrush(int type) {
    switch (type) {
        case 1:
            return new Brush();
        case 2:
            return new Pen();
        default:
            return new Brush();
    }
}