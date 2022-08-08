#include <arrow/api.h>
#include <arrow/filesystem/localfs.h>
#include <arrow/io/api.h>
#include <arrow/io/file.h>
#include <fstream>
#include <iostream>
#include <parquet/arrow/reader.h>
#include <parquet/arrow/writer.h>
#include <parquet/exception.h>
#include <parquet/stream_reader.h>

// [CRITICAL] Don't use shared_ptr
void causeSegmentationFault(const std::string &parFile, std::shared_ptr<arrow::Table> table)
{
    static const std::vector<std::shared_ptr<arrow::Field>> schema_vector = {
        arrow::field("a", arrow::int32()), arrow::field("b", arrow::int32()),   arrow::field("c", arrow::int64()),
        arrow::field("d", arrow::int64()), arrow::field("e", arrow::int32()),   arrow::field("f", arrow::int32()),
        arrow::field("g", arrow::int32()), arrow::field("h", arrow::float64()), arrow::field("i", arrow::int32()),
        arrow::field("j", arrow::int64()), arrow::field("k", arrow::int32()),
    };

    // [CRITICAL] Uncomment below code if you want to trigger segmentation fault
    // auto expected_schema = std::make_shared<arrow::Schema>(schema_vector);

    // if (!expected_schema->Equals(*table->schema()))
    // {
    //     std::cerr << "Schemas in " << parFile << " are not matching order!\n";
    //     exit(-1);
    // }
}

void readParquetToTable(const std::string &parFile, std::shared_ptr<arrow::Table> *table)
{
    arrow::Status st;
    arrow::fs::LocalFileSystem file_system;
    arrow::MemoryPool *pool = arrow::default_memory_pool();
    std::shared_ptr<arrow::io::RandomAccessFile> input = file_system.OpenInputFile(parFile).ValueOrDie();

    // Open Parquet file reader
    std::unique_ptr<parquet::arrow::FileReader> arrow_reader;
    st = parquet::arrow::OpenFile(input, pool, &arrow_reader);
    if (!st.ok())
    {
        std::cerr << "failed to open " << parFile << std::endl;
        exit(-1);
    }

    // Read entire file as a single Arrow table
    st = arrow_reader->ReadTable(table);
    if (!st.ok())
    {
        std::cerr << "failed to open " << parFile << std::endl;
        exit(-1);
    }
}

int main(int argc, const char *argv[])
{
    std::shared_ptr<arrow::Table> table;
    readParquetToTable("/root/arrow-report/input/sample.parquet", &table);
    std::cout << table->ToString() << std::endl;

    return 0;
}
