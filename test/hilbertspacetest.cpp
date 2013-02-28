#include "../hilbertspace.h"
#include <gtest/gtest.h>
#include <vector>

using namespace std;

namespace {
class HilbertSpaceTest : public ::testing::Test
{
protected:
    HilbertSpaceTest()
    {
	dims.push_back(3);
	dims.push_back(4);
    }
    
    vector<uint> dims;
};

TEST_F(HilbertSpaceTest, CreateEmptyDimension) {
    HilbertSpace space;
    EXPECT_EQ(0, space.totalDimension());
}

TEST_F(HilbertSpaceTest, CreateSpaceWithZeroDimensionSize) {
    try {
	HilbertSpace space(0);
	FAIL();
    }
    catch (exception e) 
    {
	try {
	    dims.push_back(0);
	    HilbertSpace space2(dims);
	    FAIL();
	}
	catch (exception e) {}
    }
}

TEST_F(HilbertSpaceTest, CreateTwoDimensionSpaceReturnRankIs2) {
    HilbertSpace space(dims);
    ASSERT_EQ(2, space.rank());
}

TEST_F(HilbertSpaceTest, CreateTwoDimensionSpaceReturnDimensionsAreCorrect) {
    HilbertSpace space(dims);
    EXPECT_EQ(3, space.dimension(0));
    EXPECT_EQ(4, space.dimension(1));
}

TEST_F(HilbertSpaceTest, CheckAccessToInvalidIndexIsDenied) {
    HilbertSpace space(dims);
    EXPECT_ANY_THROW(space.dimension(-1));
    EXPECT_ANY_THROW(space.dimension(space.rank()));
}

TEST_F(HilbertSpaceTest, CheckTensorProduct) {
    HilbertSpace space(dims);
    vector<uint> additionalDims;
    additionalDims.push_back(1);
    additionalDims.push_back(6);
    additionalDims.push_back(78);
    HilbertSpace additionalSpace(additionalDims);
    
    space.tensorWith(additionalSpace);
    
    EXPECT_EQ(5, space.rank());
    EXPECT_EQ(1, space.dimension(2));
    EXPECT_EQ(78, space.dimension(space.rank() - 1));
}

TEST_F(HilbertSpaceTest, CheckTotalDimension) {
    HilbertSpace space(dims);    
    EXPECT_EQ(7, space.totalDimension());
}

}
