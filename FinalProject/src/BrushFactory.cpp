#include "BrushFactory.hpp"
#include "Brush.hpp"

GeneralBrush * BrushFactory::createBrush(int type) {
    switch (type) {
        case 1:
            return new Brush();
            break;
        case 2:
            return nullptr; // leave for implement more types of brushes
            break;
        default:
            return new Brush();
    }
}