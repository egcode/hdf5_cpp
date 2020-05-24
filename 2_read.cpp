#include <string>
#include <iostream>
#include "H5Cpp.h"

// g++ 2_read.cpp -lhdf5 -lhdf5_cpp -o 2_read;./2_read

/*

rm -rf build;mkdir build;cd build;cmake \
-DCMAKE_C_COMPILER=clang \
-DCMAKE_CXX_COMPILER=clang++ \
-DCMAKE_PREFIX_PATH="$PWD/libtorch;/usr/local/Cellar/hdf5/1.12.0" ..;make VERBOSE=1;cd ..

./build/src

-------------------------------------------------------------------------------------------------


    =====================================
    *** Mean embedding h5 file structure:
    person1_name
        embedding    [4.5, 2.1, 9.9]
    person2_name
        embedding    [3.0, 41.1, 56.621]
    =====================================

    Parameters;
        h5_filename='data/dataset.h5'
        person_name='Alex'
        mean_embedding=[-1.40146054e-02,  2.31648367e-02, -8.39150697e-02......]

*/
#define MAX_NAME_LENGTH 32
const std::string FileName("SimpleCompound.h5");
const std::string DatasetName("PersonalInformation");
const std::string member_age("Age");
const std::string member_sex("Sex");
const std::string member_name("Name");
const std::string member_height("Height");

typedef struct {
    int age;
    char sex;
    char name[MAX_NAME_LENGTH];
    float height;
} PersonalInformation;

std::ostream& operator<<(std::ostream& os, const PersonalInformation& pInfo) {
    return os << "{ " << "Age: " << pInfo.age << " "
                      << "Sex: " << pInfo.sex << " "
                      << "Name: " << pInfo.name << " "
                      << "height:" << pInfo.height << " }" << std::endl;
}

int main(void)
{
    // Data to write
    PersonalInformation person_list[] = {
        { 18, 'M', "Mary",  152.0   },
        { 32, 'F', "Tom",   178.6   },
        { 29, 'M', "Tarou", 166.6   }
    };
    // the length of the data
    int length = sizeof(person_list) / sizeof(PersonalInformation);
    // the array of each length of multidimentional data.
    hsize_t dim[1];
    dim[0] = sizeof(person_list) / sizeof(PersonalInformation);

    // the length of dim
    int rank = sizeof(dim) / sizeof(hsize_t);

    std::cout << "Dim: " << dim << std::endl;
    std::cout << "rank: " << rank << std::endl;
    std::cout << "length: " << length << std::endl;
    std::cout << "sizeof(PersonalInformation): " << sizeof(PersonalInformation) << std::endl;
    std::cout << "sizeof(person_list): " << sizeof(person_list) << std::endl;

    std::cout << "sizeof(dim) : " <<  sizeof(dim) << std::endl;
    std::cout << "sizeof(hsize_t) : " << sizeof(hsize_t) << std::endl;

    // // defining the datatype to pass HDF55
    H5::CompType mtype(sizeof(PersonalInformation));
    mtype.insertMember(member_age, HOFFSET(PersonalInformation, age), H5::PredType::NATIVE_INT);
    mtype.insertMember(member_sex, HOFFSET(PersonalInformation, sex), H5::PredType::C_S1);
    mtype.insertMember(member_name, HOFFSET(PersonalInformation, name), H5::StrType(H5::PredType::C_S1, MAX_NAME_LENGTH));
    mtype.insertMember(member_height, HOFFSET(PersonalInformation, height), H5::PredType::NATIVE_FLOAT);
    
    // preparation of a dataset and a file.
    H5::DataSpace space(rank, dim);
    // H5::H5File *file = new H5::H5File(FileName, H5F_ACC_TRUNC);
    // H5::DataSet *dataset = new H5::DataSet(file->createDataSet(DatasetName, mtype, space));
    ///////// Write
    // dataset->write(person_list, mtype);
    


    const H5std_string  FILE_NAME("SimpleCompound.h5");
    H5::H5File  file(FILE_NAME, H5F_ACC_RDONLY);
    H5::DataSet dataset = file.openDataSet(DatasetName);

    /////////Read set
    PersonalInformation person_list_out[1];
    dataset.read(person_list_out, mtype);

    std::cout << "TATASET: " << person_list_out[0];


    return 0;
}