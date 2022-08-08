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

Note that function `causeSegmentationFault` is never called

Remember to check file path in

```CPP
readParquetToTable("/root/arrow-report/input/sample.parquet", &table);
```