#ifndef DATA_H
#define DATA_H

#include <QObject>

namespace BibleSlide
{
   Q_NAMESPACE         // required for meta object creation
   enum Slide {
       Title = 0,
       GridChapters,
       GridNumbersVerses,
       ListVerses,
       Error,
   };
   Q_ENUM_NS(Slide)  // register the enum in meta object data
}


#endif // DATA_H
