#include "headers/Tile.h"

Tile::Tile()
{
    this->value = 0;
}

Tile::Tile(int value)
{
    this->setValue(value);
}

int Tile::getValue()
{
    return this->value;
}

bool Tile::isEmpty()
{
    return this->getValue() == 0;
}

void Tile::setValue(int value)
{
    this->value = value;
}

bool Tile::canMergeWith(Tile other)
{
    return !merged && (other.value != 0) && !other.merged && (value == other.getValue());
}

int Tile::mergeWith(Tile other)
{
    if (canMergeWith(other))
    {
        value *= 2;
        merged = true;
        return value;
    }
    return -1;
}

void Tile::setMerged(bool m)
{
    this->merged = m;
}
