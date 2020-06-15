#ifndef DATA_H
#define DATA_H

#include <QObject>

namespace BibleEnums
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

   enum Testament{
       New_Testament,
       Old_Testament,
   };
   Q_ENUM_NS(Testament)  // register the enum in meta object data
}


#endif // DATA_H
