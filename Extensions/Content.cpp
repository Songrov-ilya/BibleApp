#include "Content.h"

Content::Content(QObject *parent) : QObject(parent)
{

}


void Content::generateContentJson(const QString pathDir)
{
    QJsonObject objMain;

    QStringList listDir = getListDirectoryContents(pathDir);
    for (const QString &str : listDir) {
        QString nameDir = QFileInfo(str).fileName();
        QStringList splitNameDir = nameDir.split("_");
        QString bookNumber = "book_";
        QJsonObject objBook;
        if(splitNameDir.size() >= 5){
            bookNumber += splitNameDir.at(0);
            QString nameEn = splitNameDir.at(2);
            QString nameRu = splitNameDir.at(1);
            QString otherInfoEn = splitNameDir.at(4);
            otherInfoEn.replace("-", " ").replace(")", "");
            QString otherInfoRu = splitNameDir.at(3);
            otherInfoRu.replace("-", " ").replace("(", "");
            objBook.insert("name_en", nameEn.replace("-", " "));
            objBook.insert("name_ru", nameRu.replace("-", " "));
            objBook.insert("other_info_en", otherInfoEn);
            objBook.insert("other_info_ru", otherInfoRu);
            objBook.insert("path_dir", pathDir + "/" + nameDir);
            QJsonObject objChapters;
            fillChapters(&objChapters, pathDir + "/" + nameDir);
            objBook.insert("photos", objChapters);

        }
        objMain.insert(bookNumber, objBook);
    }

    QJsonDocument doc(objMain);
    Helper::writeFileJson(doc, "../BibleApp/Other/" + QFileInfo(pathDir).fileName().replace("_","") + "_Content.json");
    //    {
    //    "book_08": {
    //        "name_en": "Ruth",
    //        "name_ru": "Ð ÑÑÑ",
    //        "other_info_en": "Historical Books",
    //        "other_info_ru": "ÐÑÑÐŸÑÐžÑÐµÑÐºÐžÐµ",
    //        "path_dir": "../BibleApp/Photos/Old_Testament/",
    //        "photos": {
    //            "IMG_20190604_114108_HDR.jpg": 0,
    //            "IMG_20190604_114115_HDR.jpg": 0,
    //            "IMG_20190604_114121_HDR.jpg": 0
    //        }
    //    },
    //    }
}

void Content::loadContentJson(QVector<Book> *vecBooks, const BibleEnums::Testament &testament)
{
    QJsonDocument doc;
    const QString nameFile { testament == BibleEnums::New_Testament ? File::newTestament_Content : File::oldTestament_Content};
    Helper::readFileJson(&doc, nameFile);

    QJsonObject obj = doc.object();
    for (const QString &key : obj.keys()) {
        vecBooks->push_back(Book(obj.value(key).toObject()));
    }
}

void Content::loadTextVersesJson(QVector<Book> *vecBooks, const BibleEnums::Testament &testament)
{
    QJsonDocument doc;
    Helper::readFileJson(&doc, File::bibleTextJson);
    QJsonArray arrBooks = doc.array();

    for (const QJsonValue &book: arrBooks) {
        QJsonObject objBook = book.toObject();
        QString bookName = objBook.value("name").toString();
        for (Book &book: *vecBooks) {
            if(book.getNameEn() == bookName){
                QJsonArray arrChapters = objBook.value("chapters").toArray();
                for(const QJsonValue &chapter : arrChapters){
                    book.appentChapter(Chapter(chapter.toArray()));
                }
                break;
            }
        }
    }
}


QStringList Content::getListDirectoryContents(const QString &dir)
{
    QStringList list;
    const QDir directory(dir);

    for(const QFileInfo &info: directory.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot)) {
        //        if(!info.isDir()){
        list.append(info.absoluteFilePath());
        //        }
    }
    return list;
}

void Content::fillChapters(QJsonObject *objChapters, const QString &pathDir)
{
    QStringList list = getListDirectoryContents(pathDir);
    for (const QString &str: list) {
        //        objChapters.insert(str, 0);
        objChapters->insert(QFileInfo(str).fileName(), "0");
    }
}
