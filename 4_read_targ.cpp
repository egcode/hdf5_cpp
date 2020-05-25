// g++ 4_read_targ.cpp -lhdf5 -lhdf5_cpp -o 4_read_targ;./4_read_targ

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

#ifdef OLD_HEADER_FILENAME
#include <iostream.h>
#else
#include <iostream>
#endif
using std::cout;
using std::endl;

#include <string>
#include <vector>
#include "H5Cpp.h"
using namespace H5;

const H5std_string FILE_NAME( "./data/dataset_targarien.h5" );
std::vector<std::string> groupNames;

// Operator function
extern "C" herr_t file_info(hid_t loc_id, const char *name, const H5L_info2_t *linfo,
    void *opdata);

int main(void)
{
    // Try block to detect exceptions raised by any of the calls inside it
    try
    {
        /*
         * Turn off the auto-printing when failure occurs so that we can
         * handle the errors appropriately
         */
        Exception::dontPrint();

        /*
         * Create the named file, truncating the existing one if any,
         * using default create and access property lists.
         */
        H5File *file = new H5File( FILE_NAME, H5F_ACC_RDONLY );


        /*
         * Use iterator to see the names of the objects in the file
         * root directory.
         */
        cout << endl << "Iterating over elements in the file" << endl;
        herr_t idx = H5Literate2(file->getId(), H5_INDEX_NAME, H5_ITER_INC, NULL, file_info, NULL);
        cout << endl;


        cout << "Extracted group Names: \n";
        for (int i=0; i<groupNames.size();i++ )
        {
            cout << "\textracted name: " << groupNames[i] << endl;
        }

        /*
         * Close the group and file.
         */
        delete file;
    }  // end of try block

    // catch failure caused by the H5File operations
    catch( FileIException error )
    {
        error.printErrorStack();
        return -1;
    }

    // catch failure caused by the DataSet operations
    catch( DataSetIException error )
    {
        error.printErrorStack();
        return -1;
    }

    // catch failure caused by the DataSpace operations
    catch( DataSpaceIException error )
    {
        error.printErrorStack();
        return -1;
    }

    // catch failure caused by the Attribute operations
    catch( AttributeIException error )
    {
        error.printErrorStack();
        return -1;
    }
    return 0;
}

/*
 * Operator function.
 */
herr_t
file_info(hid_t loc_id, const char *name, const H5L_info2_t *linfo, void *opdata)
{
    hid_t group;

    /*
     * Open the group using its name.
     */
    group = H5Gopen2(loc_id, name, H5P_DEFAULT);

    groupNames.push_back(name);

    /*
     * Display group name.
     */
    cout << "Name : " << name << endl;

    H5Gclose(group);
    return 0;
}

