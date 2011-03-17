#ifndef QSCRIPT_QTM_FILE_H
#define QSCRIPT_QTM_FILE_H
#include "question.h"
#include <vector>
#include <fstream>

namespace qtm_data_file {



struct Card 
{
	std::vector<char> data_;
	std::vector<char> multiPunchData_;
};

struct QtmDataFile
{
	std::vector<Card> cardVec_;
};

enum QtmFileMode 
{
	READ_EQ_0 /* flat file */,
	READ_EQ_1 /* wrap around at 1000 i.e. 1001 to 1999 is in card 1,
			2001 to 2999 is in card 2 */ ,
	READ_EQ_2 /* wrap around at 100 i.e. 101 - 199 is in card 1
			201 to 299 is in card 2 */
};

struct QtmFileCharacteristics
{
	int cardWrapAroundAt_;
	int cardStartAt_;
	bool dontBreakQuestionsAtBoundary_;
	QtmFileMode qtmFileMode_;
	int currentCard_;
	int currentColumn_;
	int multiplier_;
	QtmFileCharacteristics();
	void NextCard();
	int GetCurrentColumnPosition();
	int UpdateCurrentColumn(int width_);
	QtmFileCharacteristics(int p_cardStartAt_, int p_cardWrapAroundAt,
			bool p_dontBreakQuestionsAtBoundary, QtmFileMode p_qtmFileMode);
};

struct CodeBucket 
{
	std::vector<int> codeVec_;
	CodeBucket(): codeVec_()
	{ }
};

struct QtmDataDiskMap
{
	public:
		AbstractQuestion *q;
		int32_t startPosition_;
		int32_t width_;
		int32_t totalLength_;

		QtmDataDiskMap(AbstractQuestion * p_q, QtmFileCharacteristics & file_xcha);

		int GetTotalLength() { return totalLength_; }

		void write_data (QtmDataFile & p_qtm_data_file);
		void print_map(std::fstream & map_file);
		std::vector <CodeBucket> codeBucketVec_;

};


} /* close namespace qtm_data_file */

#endif /* QSCRIPT_QTM_FILE_H */
