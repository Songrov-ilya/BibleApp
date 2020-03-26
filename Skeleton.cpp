#include "Skeleton.h"

Skeleton::Skeleton(QObject *parent) : QObject(parent)
{
    readBibleTextJson();

}

Book Skeleton::getBook(const QString name)
{
    for (const Book &book: vecBooks) {
        if(book.getNameEn() == name){
            return book;
        }
    }
    return Book();
}

Book Skeleton::getNextBook(const QString nameCurrentBook) const
{
    for (int var = 0; var < vecBooks.size(); ++var) {
        if(vecBooks.at(var).getNameEn() == nameCurrentBook && var < vecBooks.size() - 1){
            return vecBooks.at(var + 1);
        }
    }
    return Book{};
}

Book Skeleton::getPreviousBook(const QString nameCurrentBook) const
{
    for (int var = 0; var < vecBooks.size(); ++var) {
        if(vecBooks.at(var).getNameEn() == nameCurrentBook && var > 0){
            return vecBooks.at(var - 1);
        }
    }
    return Book{};
}

QStringList Skeleton::getListBooks() const
{
    QStringList list;
    for (const Book &book: vecBooks) {
        list.append(book.getNameEn());
    }
    return list;
}

void Skeleton::loadTableOfContents()
{
    QJsonDocument doc;
    Helper::readFileJson(File::oldTestament_Content, doc);
    QJsonObject obj = doc.object();
    for (const QString &key : obj.keys()) {
        vecBooks.push_back(Book(obj.value(key).toObject()));
    }
}

void Skeleton::generateContent(QString pathDir)
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
            fillChapters(objChapters, pathDir + "/" + nameDir);
            objBook.insert("photos", objChapters);

        }
        objMain.insert(bookNumber, objBook);
    }

    QJsonDocument doc(objMain);
    Helper::writeFileJson("../BibleApp/Other/" + QFileInfo(pathDir).fileName().replace("_","") + "_Content.json", doc);
    //    {
    //    "book_08": {
    //        "name_en": "Ruth",
    //        "name_ru": "� уфь",
    //        "other_info_en": "Historical Books",
    //        "other_info_ru": "Исторические",
    //        "path_dir": "../BibleApp/Photos/Old_Testament/",
    //        "photos": {
    //            "IMG_20190604_114108_HDR.jpg": 0,
    //            "IMG_20190604_114115_HDR.jpg": 0,
    //            "IMG_20190604_114121_HDR.jpg": 0
    //        }
    //    },
    //    }
}

QStringList Skeleton::getListDirectoryContents(const QString dir)
{
    QStringList list;
    QDir directory(dir);

    for(const QFileInfo &info: directory.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot)) {
        //        if(!info.isDir()){
        list.append(info.absoluteFilePath());
        //        }
    }
    return list;
}

void Skeleton::fillChapters(QJsonObject &objChapters, QString pathDir)
{
    QStringList list = getListDirectoryContents(pathDir);
    for (const QString &str: list) {
        //        objChapters.insert(str, 0);
        objChapters.insert(QFileInfo(str).fileName(), "0");
    }
}

void Skeleton::readBibleTextJson()
{
    QJsonDocument doc;
    Helper::readFileJson(File::bibleTextJson, doc);
    QJsonArray arrMain = doc.array();
//    int count = 0;
    for (const QJsonValue &book: arrMain) {
        QJsonObject objBook = book.toObject();
        for(const QJsonValue &chapter : objBook.value("chapters").toArray()){
            QJsonArray arrChapter = chapter.toArray();
            QString strChapter {};
            for(const QJsonValue &verse : arrChapter){
                strChapter += verse.toString();
            }
            int ret = strChapter.indexOf(QTextCodec::toUnicode(QString("������")), 0, Qt::CaseInsensitive);
            if(ret != -1){
                qDebug() << "finded " << strChapter << endl;
            }
        }
//        Helper::writeFileJson("../BibleApp/TextBible/Bible_XML_and_JSON/bible-master/Chapters/" + QString::number(++count) + "__" +
//                              objBook.value("name").toString() + "_ru_synodal.json", QJsonDocument(objBook));
    }
}
