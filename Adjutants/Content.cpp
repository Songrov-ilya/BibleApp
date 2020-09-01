#include "Content.h"


void Content::loadContent_Photos(QVector<Book> *vecBooks, const BibleEnums::Testament testament)
{
    const QString dirContent = testament == BibleEnums::Old_Testament ? Path::dirContent_Old_Testament_Photos : Path::dirContent_New_Testament_Photos;
    const QString fileContent = testament == BibleEnums::Old_Testament ? Path::fileContent_Old_Testament_Photos : Path::fileContent_New_Testament_Photos;
    QJsonDocument doc;
    FileWorker::readFileJson(&doc, fileContent);

    QJsonObject obj = doc.object();
    QStringList listKeys = obj.keys();
    Q_ASSERT(listKeys.isEmpty() != vecBooks->size());

    for (int var = 0; var < testament; ++var) {
        (*vecBooks)[var].loadContentPhotos(obj.value(listKeys.at(var)).toObject(), dirContent);
    }
}

void Content::loadContenet_ArrayBooks(QStringList *list, const BibleEnums::Testament testament)
{
    const QString nameFile = testament == BibleEnums::Old_Testament ? Path::fileContent_Old_Testament_ArrayBooks_GETBIBLE : Path::fileContent_New_Testament_ArrayBooks_GETBIBLE;
    QJsonDocument doc;
    FileWorker::readFileJson(&doc, nameFile);
    QJsonArray arr = doc.array();
    std::for_each(arr.begin(), arr.end(), [list](const QJsonValue &value){ list->append(value.toString()); });
}

void Content::loadContenet_OneBook(Book *book, const BibleEnums::Testament testament)
{
    Q_ASSERT(book);
    const QString dirContent = testament == BibleEnums::Old_Testament ? Path::dirContent_Old_Testament_JsonText_GETBIBLE : Path::dirContent_New_Testament_JsonText_GETBIBLE;
    const QString pathBook = dirContent + getIndexBookStr(book->getIndexBook()) + ".json";
    QJsonDocument doc;
    FileWorker::readFileJson(&doc, pathBook);
    book->loadContentChapterText(doc.array());
}

QString Content::getIndexBookStr(const int index)
{
    return "book_" + QString::number(index).rightJustified(2, '0');
}
