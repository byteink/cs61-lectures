#include "qslib.hh"

int main(int argc, char* argv[]) {
    qs_info qsi = parse_arguments(argc, argv);
    double start = timestamp();

    // create sorted list by insertion
    std::list<int> list;
    for (int i = 0; i != qsi.size; ++i) {
        int value = qsi.array[i];

        // find first position in list that's > value
        auto pos = std::find_if(list.begin(), list.end(),
                                [=] (int x) { return x > value; });

        // insert value there
        list.insert(pos, value);
    }

    printf("created list in %.06f sec\n", timestamp() - start);
    ints_print(list);

    // check that the collection is sorted
    assert(ints_sorted(list));
    // check that the sorted collection contains the same data
    // (this can be fooled, but it's better than nothing!)
    assert(ints_checksum(list) == qsi.checksum);

    delete[] qsi.array;
}
