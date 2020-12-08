#include "GeneralBrush.hpp"

/*! \brief Brush factory class which initialize brush instance.
 *
 */
class BrushFactory {
private:

public:
    GeneralBrush* createBrush(int type);
};
