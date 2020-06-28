#include "Content.h"

Content::Content(QObject *parent) : QObject(parent)
{

}

void Content::generateContenet_JsonText()
{
    QJsonDocument doc;
    Helper::readFileJson(&doc, Path::allBibleTextJson);
    QJsonArray arrMain = doc.array();

    QString pathDirTestament { Path::dirContenet_Old_Testament_JsonText };
    for (int var = 0; var < arrMain.size(); ++var) {
        QJsonObject objBook = arrMain.at(var).toObject();
        Helper::writeFileJson(QJsonDocument(objBook), pathDirTestament + QString::number(var, 'g', 2) + ".json");
        if (var >= BibleEnums::Old_Testament) {
            pathDirTestament = Path::dirContenet_New_Testament_JsonText;
        }
    }
}


void Content::generateContent_Photos()
{
    QJsonObject objMainOld;
    QStringList listDirOld = getListFileInDirectory(Path::dirContenet_Old_Testament_Photos );
    for (int var = 0; var < listDirOld.size(); ++var) {
        const QString bookNumber = Helper::getNumberStr(var);
        const QString keyBookNumber = "book_" + bookNumber;
        QJsonObject objBook;
        fillPhotos(&objBook, Path::dirContenet_Old_Testament_Photos  + bookNumber);
        objMainOld.insert(bookNumber, objBook);
    }
    Helper::writeFileJson(QJsonDocument(objMainOld), Path::content_Old_Testament_Photos);

    QJsonObject objMainNew;
    QStringList listDirNew = getListFileInDirectory(Path::dirContenet_New_Testament_Photos );
    for (int var = 0; var < listDirNew.size(); ++var) {
        const QString bookNumber = Helper::getNumberStr(var);
        const QString keyBookNumber = "book_" + bookNumber;
        QJsonObject objBook;
        fillPhotos(&objBook, Path::dirContenet_New_Testament_Photos  + bookNumber);
        objMainNew.insert(bookNumber, objBook);
    }
    Helper::writeFileJson(QJsonDocument(objMainNew), Path::content_New_Testament_Photos);

//    QString pathDirTestament { Path::dirContenet_Old_Testament_Photos };
//    for (int var = 0; var < 2; ++var) {
//        if (var >= 1) {
//            pathDirTestament = Path::dirContenet_New_Testament_Photos;
//        }

//        QStringList listDir = getListFileInDirectory(pathDirTestament);
//        for (int var = 0; var < listDir.size(); ++var) {
//            const QString bookNumber = Helper::getNumberStr(var);
//            const QString keyBookNumber = "book_" + bookNumber;
//            QJsonObject objBook;
//            fillPhotos(&objBook, pathDirTestament + bookNumber);
//            objMain.insert(bookNumber, objBook);
//        }
//        for (const QString &str : listDir) {
//            QString nameDir = QFileInfo(str).fileName();
//            QStringList splitNameDir = nameDir.split("_");
//            QString bookNumber = "book_";
//            QJsonObject objBook;
//            if(splitNameDir.size() >= 5){
//                bookNumber += splitNameDir.at(0);
//                QString nameEn = splitNameDir.at(2);
//                QString nameRu = splitNameDir.at(1);
//                QString otherInfoEn = splitNameDir.at(4);
//                otherInfoEn.replace("-", " ").replace(")", "");
//                QString otherInfoRu = splitNameDir.at(3);
//                otherInfoRu.replace("-", " ").replace("(", "");
//                objBook.insert("name_en", nameEn.replace("-", " "));
//                objBook.insert("name_ru", nameRu.replace("-", " "));
//                objBook.insert("family_books_en", otherInfoEn);
//                objBook.insert("family_books_ru", otherInfoRu);
//                objBook.insert("path_dir_photos", pathDir + "/" + nameDir);
//                QJsonObject objChapters;
//                fillPhotos(&objChapters, pathDir + "/" + nameDir);
//                objBook.insert("photos", objChapters);

//            }
//        }

//        QJsonDocument doc(objMain);
//        Helper::writeFileJson(doc, "../BibleApp/Other/" + QFileInfo(pathDir).fileName().replace("_","") + ".json");
//    }

    //    {
    //    "book_08": {
    //        "name_en": "Ruth",
    //        "name_ru": "Ð ÑÑÑ",
    //        "family_books_en": "Historical Books",
    //        "family_books_ru": "ÐÑÑÐŸÑÐžÑÐµÑÐºÐžÐµ",
    //        "path_dir_photos": "../BibleApp/Photos/Old_Testament/",
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
    const QString nameFile { testament == BibleEnums::New_Testament ? Path::content_New_Testament_Photos : Path::content_Old_Testament_Photos};
                             Helper::readFileJson(&doc, nameFile);

                                                  QJsonObject obj = doc.object();
                                                                       for (const QString &key : obj.keys()) {
                                                                           vecBooks->push_back(Book(obj.value(key).toObject()));
                                                                       }
                           }

    void Content::loadTextVersesJson(QVector<Book> *vecBooks, const BibleEnums::Testament &testament)
    {
        QJsonDocument doc;
        Helper::readFileJson(&doc, Path::allBibleTextJson);
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


    QStringList Content::getListFileInDirectory(const QString &dir)
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

    void Content::fillPhotos(QJsonObject *objBook, const QString &pathDir)
    {
        QStringList list = getListFileInDirectory(pathDir);
        for (const QString &str: list) {
            objBook->insert(QFileInfo(str).fileName(), "0");
        }
    }
