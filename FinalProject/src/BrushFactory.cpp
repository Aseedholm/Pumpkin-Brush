#include "BrushFactory.hpp"
#include "Brush.hpp"
#include "Pen.hpp"

/*! \brief Create function which takes in an argument and return a brush instance
 *
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