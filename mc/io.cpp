#include "io.hpp"

Reader::Reader(std::string filepath)
: filepath(filepath)
{
}

ReaderTxt::ReaderTxt(std::string filepath)
: filepath(filepath)
{
    *this->parser()
}