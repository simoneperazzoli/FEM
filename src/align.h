#ifndef ALIGN_H_
#define ALIGN_H_

#include <emmintrin.h>
#include <smmintrin.h>

#include "sequence_batch.h"
#include "utils.h"

#define ALPHABET_SIZE 5
#define NUM_VPU_LANES 8

uint32_t verify_candidates(const FEMArgs *fem_args, const SequenceBatch *read_sequence_batch, uint32_t read_sequence_index, uint8_t direction, const SequenceBatch *reference_sequence_batch, const uint64_t *candidates, uint32_t num_candidates, kvec_t_Mapping *mappings);
uint32_t process_mappings(const FEMArgs *fem_args, const SequenceBatch *read_sequence_batch, uint32_t read_sequence_index, const SequenceBatch *reference_sequence_batch, Mapping *mappings, uint32_t num_mappings, kvec_t_bam1_t_ptr *sam_alignment_kvec);
int banded_edit_distance(const FEMArgs *fem_args, const char *pattern, const char *text, int read_length, int *mapping_end_position);
void vectorized_banded_edit_distance(const FEMArgs *fem_args, const uint32_t vpu_index, const SequenceBatch *reference_sequence_batch, const char *text, int read_length, const uint64_t *candidates, uint32_t num_candidates, int16_t *mapping_edit_distances, int16_t *mapping_end_positions);
int generate_alignment(const FEMArgs *fem_args, const char *pattern, const char *text, int read_length, int mapping_edit_distance, int mapping_end_position, kvec_t_uint32_t *cigar_uint32_t, kstring_t *MD_tag);
void generate_MD_tag(const char *pattern, const char *text, int mapping_start_position, const kvec_t_uint32_t *cigar, kstring_t *MD);
void generate_bam1_t(uint8_t edit_distance, kstring_t *MD_tag, uint32_t mapping_start_position, int32_t reference_sequence_index, uint8_t mapping_quality, uint16_t flag, const char *query_name, uint16_t query_name_length, uint32_t *cigar, uint32_t num_cigar_operations, const char *query, const char *query_qual, int32_t query_length, bam1_t *sam_alignment);
#endif // ALIGN_H_
