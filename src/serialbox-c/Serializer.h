/*===-- serialbox-c/Serializer.h ----------------------------------------------------*- C++ -*-===*\
 *
 *                                    S E R I A L B O X
 *
 * This file is distributed under terms of BSD license.
 * See LICENSE.txt for more information
 *
 *===------------------------------------------------------------------------------------------===//
 *
 *! \file
 *! This file contains the C implementation of the Serializer.
 *
\*===------------------------------------------------------------------------------------------===*/

#ifndef SERIALBOX_C_SERIALIZER_H
#define SERIALBOX_C_SERIALIZER_H

#include "serialbox-c/Type.h"

#ifdef __cplusplus
extern "C" {
#endif

/*===------------------------------------------------------------------------------------------===*\
 *     Construction & Destruction
\*===------------------------------------------------------------------------------------------===*/

/**
 * \brief Create a new Serializer
 *
 * \param mode         Mode of the Serializer
 * \param directory    Directory of the Archive and Serializer meta-data
 * \param prefix       Prefix of all filenames
 * \param archiveName  Name of Archive (e.g "BinaryArchive")
 *
 * \return refrence to the newly constructed Serializer or NULL if an error occurred
 *
 * This will read ´MetaData-prefix.json´ to initialize the Serializer and construct the Archive by
 * reading the ´ArchiveMetaData-prefix.json´.
 */
serialboxSerializer_t* serialboxSerializerCreate(serialboxOpenModeKind mode, const char* directory,
                                                 const char* prefix, const char* archive);

/**
 * \brief Destroy the serializer and deallocate all memory
 *
 * \param serializer  Serializer to use
 */
void serialboxSerializerDestroy(serialboxSerializer_t* serializer);

/*===------------------------------------------------------------------------------------------===*\
 *     Utility
\*===------------------------------------------------------------------------------------------===*/

/**
 * \brief Return mode of the Serializer
 *
 * \param serializer  Serializer to use
 * \return mode of the Serializer
 */
serialboxOpenModeKind serialboxSerializerGetMode(const serialboxSerializer_t* serializer);

/**
 * \brief Return the directory of the Serializer
 *
 * \param serializer  Serializer to use
 * \return directory of the Serializer as a null-terminated string
 */
const char* serialboxSerializerGetDirectory(const serialboxSerializer_t* serializer);

/**
 * \brief Return the prefix of all filenames
 *
 * \param serializer  Serializer to use
 * \return prefix of the Serializer as a null-terminated string
 */
const char* serialboxSerializerGetPrefix(const serialboxSerializer_t* serializer);

/**
 * \brief Write meta-data to disk
 *
 * \param serializer  Serializer to use
 */
void serialboxSerializerUpdateMetaData(serialboxSerializer_t* serializer);

/**
 * \brief Indicate whether serialization is enabled [default: enabled]
 */
extern int serialboxSerializationEnabled;

/**
 * \brief Enabled serialization
 */
void serialboxEnableSerialization(void);

/**
 * \brief Disable serialization
 */
void serialboxDisableSerialization(void);

/*===------------------------------------------------------------------------------------------===*\
 *     Global Meta-information
\*===------------------------------------------------------------------------------------------===*/

/**
 * \brief Allocate a new ´serialboxMetaInfo_t´ which maps to the global meta-information of the
 * Serializer
 *
 * \param serializer  Serializer to use
 * \return global meta-information of the serializer
 */
serialboxMetaInfo_t* serialboxSerializerGetGlobalMetaInfo(serialboxSerializer_t* serializer);

/*===------------------------------------------------------------------------------------------===*\
 *     Register and Query Savepoints
\*===------------------------------------------------------------------------------------------===*/

/**
 * \brief Register savepoint ´savepoint´ within the serializer
 *
 * \param serializer  Serializer to use
 * \param savepoint   Savepoint to add
 * \return 1 if savepoint was added successfully, 0 otherwise
 */
int serialboxSerializerAddSavepoint(serialboxSerializer_t* serializer,
                                    const serialboxSavepoint_t* savepoint);

/**
 * \brief Get number of registered savepoints
 *
 * \param serializer  Serializer to use
 * \return Number of registered savepoints
 */
int serialboxSerializerGetNumSavepoints(const serialboxSerializer_t* serializer);

/**
 * \brief Get an array of \b refrences to the registered savepoints
 *
 * To deallocate the vector use ´serialboxSerializerDestroySavepointVector´.
 *
 * \param serializer  Serializer to use
 * \return Newly allocated array of savepoints of length ´serialboxSerializerGetNumSavepoints´
 */
serialboxSavepoint_t**
serialboxSerializerGetSavepointVector(const serialboxSerializer_t* serializer);

/**
 * \brief Deallocate a savepoint vector retrieved via ´serialboxSerializerGetSavepointVector´
 *
 * \param savepointVector   Savepoint vector to deallocate
 * \param len               Length of the savepoint vector (usually obtained at the time of
 *                          allocation via ´serialboxSerializerGetNumSavepoints´)
 */
void serialboxSerializerDestroySavepointVector(serialboxSavepoint_t** savepointVector, int len);

/*===------------------------------------------------------------------------------------------===*\
 *     Register and Query Fields
\*===------------------------------------------------------------------------------------------===*/

/**
 * \brief Register field given as ´fieldMetaInfo´ within the serializer
 *
 * \param serializer  Serializer to use
 * \param name        Name of the field to register
 * \param field       Field meta-information
 * \return 1 if field was added successfully, 0 otherwise
 */
int serialboxSerializerAddField(serialboxSerializer_t* serializer, const char* name,
                                const serialboxFieldMetaInfo_t* fieldMetaInfo);

/**
 * \brief Register ´field´ within the serializer
 *
 * This function behaves the same as in older versions of serialbox.
 *
 * \param name              The name of the field
 * \param type              TypeID of the field
 * \param bytesPerElement   The size in bytes of a scalar value (e.g. 8 for doubles)
 * \param iSize             The size of the first dimension
 * \param jSize             The size of the second dimension
 * \param kSize             The size of the third dimension
 * \param lsize             The size of the fourth dimension
 * \param iMinusHalo        The dimension of the halo in negative i-direction
 * \param iPlusHalo         The dimension of the halo in positive i-direction
 * \param jMinusHalo        The dimension of the halo in negative j-direction
 * \param jPlusHalo         The dimension of the halo in positive j-direction
 * \param kMinusHalo        The dimension of the halo in negative k-direction
 * \param kPlusHalo         The dimension of the halo in positive k-direction
 * \param lMinusHalo        The dimension of the halo in negative l-direction
 * \param lPlusHalo         The dimension of the halo in positive l-direction
 * \return 1 if field was added successfully, 0 otherwise
 */
int serialboxSerializerAddField2(serialboxSerializer_t* serializer, const char* name,
                                  serialboxTypeID type, int bytesPerElement, int iSize, int jSize,
                                  int kSize, int lSize, int iMinusHalo, int iPlusHalo,
                                  int jMinusHalo, int jPlusHalo, int kMinusHalo, int kPlusHalo,
                                  int lMinusHalo, int lPlusHalo);

/**
 * \brief Get an array of C-strings of all names of the registered fields
 *
 * The function will allocate a sufficiently large array of ´char*´. Each element (as well as the
 * array itself) needs to be freed by the user using free().
 *
 * \param[in]  serializer  Serializer to use
 * \param[out] fieldnames  Array of length ´len´ of C-strings of the names of all registered fields
 * \param[out] len         Length of the array
 */
void serialboxSerializerGetFieldnames(const serialboxSerializer_t* serializer, char*** fieldnames,
                                      int* len);

/**
 * \brief Get FieldMetaInfo of field with name ´name´
 *
 * \param serializer  Serializer to use
 * \param name        Name of the field to search for
 * \return Refrence to the FieldMetaInfo if field exists, NULL otherwise
 */
serialboxFieldMetaInfo_t*
serialboxSerializerGetFieldMetaInfo(const serialboxSerializer_t* serializer, const char* name);

/**
 * \brief Get an array of C-strings of the field names registered at ´savepoint´
 *
 * The function will allocate a sufficiently large array of ´char*´. Each element (as well as the
 * array itself) needs to be freed by the user using free().
 *
 * \param[in]  serializer  Serializer to use
 * \param[in]  savepoint   Savepoint of intrest
 * \param[out] fieldnames  Array of length ´len´ of C-strings of the names of all registered fields
 * \param[out] len         Length of the array
 */
void serialboxSerializerGetFieldnamesAtSavepoint(const serialboxSerializer_t* serializer,
                                                 const serialboxSavepoint_t* savepoint,
                                                 char*** fieldnames, int* len);

/*===------------------------------------------------------------------------------------------===*\
 *     Writing & Reading
\*===------------------------------------------------------------------------------------------===*/

/**
 * \brief Serialize field ´name´ (given by ´originPtr´ and ´strides´) at ´savepoint´ to disk
 *
 * The ´savepoint´ will be registered at field ´name´ if not yet present. The ´origingPtr´ represent
 * the memory location of the first element in the array i.e skipping all initial padding.
 *
 * \param name         Name of the field
 * \param savepoint    Savepoint to at which the field will be serialized
 * \param originPtr    Pointer to the origin of the data
 * \param strides      Array of strides of length ´numStrides´
 * \param numStrides   Number of strides
 */
void serialboxSerializerWrite(serialboxSerializer_t* serializer, const char* name,
                              const serialboxSavepoint_t* savepoint, void* originPtr,
                              const int* strides, int numStrides);

/**
 * \brief Deserialize field ´name´ (given by ´originPtr´ and ´strides´) at ´savepoint´ from disk
 *
 * The ´origingPtr´ represent the memory location of the first element in the array i.e skipping
 * all initial padding.
 *
 * \param name         Name of the field
 * \param savepoint    Savepoint to at which the field will be serialized
 * \param originPtr    Pointer to the origin of the data
 * \param strides      Array of strides of length ´numStrides´
 * \param numStrides   Number of strides
 */
void serialboxSerializerRead(serialboxSerializer_t* serializer, const char* name,
                             const serialboxSavepoint_t* savepoint, void* originPtr,
                             const int* strides, int numStrides);

#ifdef __cplusplus
}
#endif

#endif