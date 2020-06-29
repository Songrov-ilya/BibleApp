#ifndef DATA_H
#define DATA_H

#include <QObject>


//#define BIBLE_SIMPLE
#define BIBLE_HARD

namespace BibleEnums
{
   Q_NAMESPACE         // required for meta object creation
   enum Slide {
       Title = 0,
       GridBooks,
       GridChapters,
       ListVerses,
       Error,
   };
   Q_ENUM_NS(Slide)  // register the enum in meta object data

   enum Testament{
       Old_Testament = 39,
       New_Testament = 27,
   };
   Q_ENUM_NS(Testament)  // register the enum in meta object data
}


namespace Path {
#ifdef QT_DEBUG
    const QString fileContent_New_Testament_Photos      = "../BibleApp/Resource/Content/Content_New_Testament_Photos.json";
    const QString fileContent_Old_Testament_Photos      = "../BibleApp/Resource/Content/Content_Old_Testament_Photos.json";
    const QString fileContent_New_Testament_Info        = "../BibleApp/Resource/Content/Content_New_Testament_Info.json";
    const QString fileContent_Old_Testament_Info        = "../BibleApp/Resource/Content/Content_Old_Testament_Info.json";
    const QString fileContent_Old_Testament_ArrayBooks  = "../BibleApp/Resource/Content/Content_Old_Testament_ArrayBooks.json";
    const QString fileContent_New_Testament_ArrayBooks  = "../BibleApp/Resource/Content/Content_New_Testament_ArrayBooks.json";
    const QString dirContent_Old_Testament_Photos       = "../BibleApp/Resource/Content/Old_Testament_Photos/";
    const QString dirContent_New_Testament_Photos       = "../BibleApp/Resource/Content/New_Testament_Photos/";
    const QString dirContent_Old_Testament_JsonText     = "../BibleApp/Resource/Content/Old_Testament_JsonText/";
    const QString dirContent_New_Testament_JsonText     = "../BibleApp/Resource/Content/New_Testament_JsonText/";
    const QString allBibleJsonText                  = "../BibleApp/Resource/Content/ru_synodal.json";
#else
    const QString newTestament_Content = ":/Skeleton/Resource/Skeleton/Content_New_Testament_Photos.json";
    const QString oldTestament_Content = ":/Skeleton/Resource/Skeleton/Content_Old_Testament_Photos.json";
    const QString bibleTextJson = ":/Skeleton/Resource/Skeleton/ru_synodal.json";
#endif
}


#endif // DATA_H
