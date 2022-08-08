# Arror Report

To run this example:

```bash
./compile.sh
./build/main
```

Please check code in src/main.cpp.

If you want to trigger **segmentation fault**, just uncomment this code:

```CPP
    // [CRITICAL] Uncomment below code if you want to trigger segmentation fault
    // auto expected_schema = std::make_shared<arrow::Schema>(schema_vector);

    // if (!expected_schema->Equals(*table->schema()))
    // {
    //     std::cerr << "Schemas in " << parFile << " are not matching order!\n";
    //     exit(-1);
    // }
```

Segmentation fault backtrack stack info:

```
(gdb) bt
#0  0x00007ffff62a66b4 in arrow::Schema::num_fields() const () from /lib64/libarrow.so.900
#1  0x00007ffff79d8fc1 in parquet::arrow::SchemaManifest::Make(parquet::SchemaDescriptor const*, std::shared_ptr<arrow::KeyValueMetadata const> const&, parquet::ArrowReaderProperties const&, parquet::arrow::SchemaManifest*) () from /lib64/libparquet.so.900
#2  0x00007ffff79a2d75 in parquet::arrow::FileReader::Make(arrow::MemoryPool*, std::unique_ptr<parquet::ParquetFileReader, std::default_delete<parquet::ParquetFileReader> >, parquet::ArrowReaderProperties const&, std::unique_ptr<parquet::arrow::FileReader, std::default_delete<parquet::arrow::FileReader> >*) () from /lib64/libparquet.so.900
#3  0x00007ffff79a2fe1 in parquet::arrow::FileReaderBuilder::Build(std::unique_ptr<parquet::arrow::FileReader, std::default_delete<parquet::arrow::FileReader> >*) () from /lib64/libparquet.so.900
#4  0x00007ffff79a3d99 in parquet::arrow::OpenFile(std::shared_ptr<arrow::io::RandomAccessFile>, arrow::MemoryPool*, std::unique_ptr<parquet::arrow::FileReader, std::default_delete<parquet::arrow::FileReader> >*) ()
   from /lib64/libparquet.so.900
#5  0x00000000004037e1 in readParquetToTable (parFile="/root/arrow-report/input/sample.parquet", table=0x7fffffffda40) at /root/arrow-report/src/main.cpp:41
#6  0x00000000004039fc in main (argc=1, argv=0x7fffffffdb68) at /root/arrow-report/src/main.cpp:60
```

Note that function `causeSegmentationFault` is never called

Remember to check file path in

```CPP
readParquetToTable("/root/arrow-report/input/sample.parquet", &table);
```