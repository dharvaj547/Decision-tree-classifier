#include <iostream>
#include <cctype>
#include <cstdlib>
#include <vector>

#define nullptr 0

// flags to enable tests for the later parts of the assignment
#define ENABLE_TASK_TESTS
#define ENABLE_NODE_TESTS
#define ENABLE_DATASET_TESTS
#define ENABLE_DECISIONTREE_TESTS

// include headers for classes being tested
#ifdef ENABLE_NODE_TESTS
#include "Binary/BinaryNode.hpp"
#endif
#ifdef ENABLE_DATASET_TESTS
#include "Binary/BinaryDataset.hpp"
#endif
#ifdef ENABLE_DECISIONTREE_TESTS
#include "Binary/BinaryDecisionTree.hpp"
#endif

using namespace std;

// This sigma value is the acceptable range of error for floating point (double) calculations
const double SIGMA = 0.001;

/*
The outcome of each test case is described by this enum, which should make the result more obvious
than if a boolean value was used in its place.
*/
enum TestResult { TR_PASS, TR_FAIL };

/*
Helper macro to eliminate a lot of of code repetition. Macros aren't the best, but this is an easy
way to get what we want.
*/

#define ASSERT(condition)                                                       \
if ((condition) == false) {                                                     \
  cout << "FAILURE: " << __FILE__ << ":" << __LINE__ << "\n"                    \
  << "\tExpression '" << #condition << "' evaluated to false" << endl;          \
  return TR_FAIL;                                                               \
}

#define ASSERT_EQUALS(actual, expected)                                         \
if (actual != expected) {                                                       \
  cout << "FAILURE: " << __FILE__ << ":" << __LINE__ << "\n"                    \
  << "\tExpected '" << expected << "' but was '" << actual << "'" << endl;      \
  return TR_FAIL;                                                               \
}

/*
Helper macro to simplify the checking of double values against expected results. Directly comparing
values would result in brittle tests, so we have to instead check if the value we got is acceptably
close to the expected value.
*/
#define EXPECT_SIGMA(value, expected)                                                                \
{                                                                                                    \
  double value_eval = value;                                                                         \
  double expected_eval = expected;                                                                   \
  if (value_eval <= (expected_eval - SIGMA) || value_eval > (expected_eval + SIGMA)) {               \
    cout << "FAILURE: " << __FILE__ << ":" << __LINE__ << "\n"                                       \
    << "\tFloating-point value " << value_eval << " differed from expected value " << expected_eval  \
    << " by more than " << SIGMA << endl;                                                            \
    return TR_FAIL;                                                                                  \
  }                                                                                                  \
}

#ifdef ENABLE_TASK_TESTS
  TestResult BaseTest() {
    // if this fails then there is a problem
    // should pass to makesure nullptr = NULL = 0
    ASSERT_EQUALS(nullptr, 0);

    return TR_PASS;
  }
  
#endif /*ENABLE_TASK_TESTS*/
#ifdef ENABLE_NODE_TESTS
  TestResult NodeGetAndSet(){

    BinaryNode *BaseNode = new BinaryNode();
    BinaryNode *Y_Node = new BinaryNode();
    BinaryNode *N_Node = new BinaryNode();

    ASSERT_EQUALS(BaseNode->getNodeN(),nullptr);
    ASSERT_EQUALS(BaseNode->getNodeY(),nullptr);
    BaseNode->setNodeN(N_Node);
    BaseNode->setNodeY(Y_Node);
    ASSERT_EQUALS(BaseNode->getNodeN(),N_Node);
    ASSERT_EQUALS(BaseNode->getNodeY(),Y_Node);

    BaseNode->setDecisionCriterion(0.5);
    ASSERT_EQUALS(BaseNode->getDecisionCriterion(),0.5);

    BaseNode->setDecisionDim(3);
    ASSERT_EQUALS(BaseNode->getDecisionDim(),3);

    BaseNode->setImpurity(0.7);
    ASSERT_EQUALS(BaseNode->getImpurity(),0.7);

    BaseNode->setLabel(-1);
    ASSERT_EQUALS(BaseNode->getLabel(),-1);
    BaseNode->setLabel(1);
    ASSERT_EQUALS(BaseNode->getLabel(),1);

    delete BaseNode;

    return TR_PASS;

  }

  TestResult NodeIsLeafBasic(){

    BinaryNode *BaseNode = new BinaryNode();
    BinaryNode *Y_Node = new BinaryNode();
    BinaryNode *N_Node = new BinaryNode();

    BaseNode->setNodeN(N_Node);
    BaseNode->setNodeY(Y_Node);

    ASSERT(!BaseNode->isLeaf());
    ASSERT(Y_Node->isLeaf());
    ASSERT(N_Node->isLeaf());

    delete BaseNode;
    delete Y_Node;
    delete N_Node;

    // OWN TESTS
    BinaryNode *headNode = new BinaryNode();
    BinaryNode *childNode1 = new BinaryNode();
    BinaryNode *childNode2 = new BinaryNode();
    BinaryNode *childNode3 = new BinaryNode();
    BinaryNode *childNode4 = new BinaryNode();
    BinaryNode *childNode5 = new BinaryNode();
    BinaryNode *childNode6 = new BinaryNode();
    BinaryNode *childNode7 = new BinaryNode();
    BinaryNode *childNode8 = new BinaryNode();
    BinaryNode *childNode9 = new BinaryNode();
    BinaryNode *childNode10 = new BinaryNode();

    headNode->setNodeY(childNode1);
    headNode->setNodeN(childNode2);
    childNode1->setNodeY(childNode3);
    childNode1->setNodeN(childNode4);
    childNode2->setNodeY(childNode5);
    childNode2->setNodeN(childNode6);
    childNode4->setNodeY(childNode7);
    childNode4->setNodeN(childNode8);
    childNode8->setNodeY(childNode9);
    childNode6->setNodeN(childNode10);

    ASSERT(!headNode->isLeaf());
    ASSERT(!childNode1->isLeaf());
    ASSERT(!childNode2->isLeaf());
    ASSERT(childNode3->isLeaf());
    ASSERT(!childNode4->isLeaf());
    ASSERT(childNode5->isLeaf());
    ASSERT(!childNode6->isLeaf());
    ASSERT(childNode7->isLeaf());
    ASSERT(!childNode8->isLeaf());
    ASSERT(childNode9->isLeaf());
    ASSERT(childNode10->isLeaf());

    delete headNode;
    delete childNode1;
    delete childNode2;
    delete childNode3;
    delete childNode4;
    delete childNode5;
    delete childNode6;
    delete childNode7;
    delete childNode8;
    delete childNode9;
    delete childNode10;

    return TR_PASS;
  }

#endif /*ENABLE_NODE_TESTS*/
#ifdef ENABLE_DATASET_TESTS

  TestResult DatasetGetAndSet() {

    BinaryDataset *Dataset = new BinaryDataset();

    ASSERT_EQUALS(Dataset->getNumFeatures(),0);
    ASSERT_EQUALS(Dataset->getNumObservations(),0);

    Dataset->setNumFeatures(100000);
    Dataset->setNumObservations(200000);

    ASSERT_EQUALS(Dataset->getNumFeatures(),100000);
    ASSERT_EQUALS(Dataset->getNumObservations(),200000);

    delete Dataset;

    // MY OWN TESTS
    BinaryDataset *dataset2 = new BinaryDataset();

    dataset2->setLabel(0, -100000);
    ASSERT_EQUALS(dataset2->getLabel(0), -1);

    dataset2->setLabel(0, -1);
    ASSERT_EQUALS(dataset2->getLabel(0), -1);

    dataset2->setLabel(0, 100000);
    ASSERT_EQUALS(dataset2->getLabel(0), 1);

    dataset2->setLabel(0, 1);
    ASSERT_EQUALS(dataset2->getLabel(0), 1);

    delete dataset2;

    return TR_PASS;
  }
  
  TestResult DatasetSplitLOO(){

    BinaryDataset *dataset = new BinaryDataset("Datasets/dataset_in6.txt", 2);
    BinaryDataset *dataset_holdin = new BinaryDataset();
    BinaryDataset *dataset_holdout = new BinaryDataset();

    ASSERT_EQUALS(dataset->getNumObservations(),20);
    ASSERT_EQUALS(dataset->getNumFeatures(),2);

    dataset->splitLOO(3, dataset_holdin, dataset_holdout);
    ASSERT_EQUALS(dataset_holdin->getNumObservations(),19);
    ASSERT_EQUALS(dataset_holdin->getNumFeatures(),2);
    ASSERT_EQUALS(dataset_holdout->getNumObservations(),1);
    ASSERT_EQUALS(dataset_holdout->getNumFeatures(),2);

    delete dataset;
    delete dataset_holdin;
    delete dataset_holdout;

    return TR_PASS;
  }

  TestResult DatasetSplit(){

    BinaryDataset *dataset = new BinaryDataset("Datasets/dataset_in6.txt", 2);
    BinaryDataset *dataset_holdin = new BinaryDataset();
    BinaryDataset *dataset_holdout = new BinaryDataset();

    ASSERT_EQUALS(dataset->getNumObservations(),20);
    ASSERT_EQUALS(dataset->getNumFeatures(),2);

    dataset->split(0,0, dataset_holdin, dataset_holdout);
    ASSERT_EQUALS(dataset_holdin->getNumObservations(),17);
    ASSERT_EQUALS(dataset_holdin->getNumFeatures(),2);
    ASSERT_EQUALS(dataset_holdout->getNumObservations(),3);
    ASSERT_EQUALS(dataset_holdout->getNumFeatures(),2);

    delete dataset;
    delete dataset_holdin;
    delete dataset_holdout;

    return TR_PASS;
  }

  TestResult DatasetOptimalSplit(){

    BinaryDataset *dataset = new BinaryDataset("Datasets/dataset_in6.txt", 2);
    BinaryDataset *dataset_holdin = new BinaryDataset();
    BinaryDataset *dataset_holdout = new BinaryDataset();
    unsigned int dim, ix;
    unsigned int *out_dim = &dim;
    unsigned int *out_ix = &ix;
    dataset->findOptimalSplit(out_dim,out_ix);
    ASSERT_EQUALS(dim,0);
    ASSERT_EQUALS(ix,0);

    delete dataset;
    delete dataset_holdin;
    delete dataset_holdout;

    BinaryDataset *dataset1 = new BinaryDataset("Datasets/dataset_in4.txt", 3);
    BinaryDataset *dataset1_holdin = new BinaryDataset();
    BinaryDataset *dataset1_holdout = new BinaryDataset();
    dataset1->findOptimalSplit(out_dim,out_ix);
    ASSERT_EQUALS(dim,2);
    ASSERT_EQUALS(ix,12);

    delete dataset1;
    delete dataset1_holdin;
    delete dataset1_holdout;

    BinaryDataset *dataset2 = new BinaryDataset("Datasets/dataset_in2.txt", 2);
    BinaryDataset *dataset2_holdin = new BinaryDataset();
    BinaryDataset *dataset2_holdout = new BinaryDataset();

    dataset2->findOptimalSplit(out_dim,out_ix);
    ASSERT_EQUALS(ix,2);
    ASSERT_EQUALS(dim,1);

    delete dataset2;
    delete dataset2_holdin;
    delete dataset2_holdout;

    return TR_PASS;
  }



#endif /*ENABLE_DATASET_TESTS*/
#ifdef ENABLE_DECISIONTREE_TESTS
  TestResult DecisionTreeGrow(){

    BinaryDataset *dataset = new BinaryDataset("Datasets/dataset_in6.txt", 2);
    BinaryDecisionTree* Tree = new BinaryDecisionTree(dataset);

    Tree->print();
    cout << Tree->size() << endl;

    ASSERT(Tree->getRoot()->getNodeN()->isLeaf());
    ASSERT(Tree->getRoot()->getNodeY()->getNodeY()->getNodeY()->isLeaf());
    ASSERT(Tree->getRoot()->getNodeY()->getNodeY()->getNodeN()->isLeaf());
    ASSERT(Tree->getRoot()->getNodeY()->getNodeN()->getNodeY()->isLeaf());
    ASSERT(Tree->getRoot()->getNodeY()->getNodeN()->getNodeN()->getNodeY()->isLeaf());
    ASSERT(Tree->getRoot()->getNodeY()->getNodeN()->getNodeN()->getNodeN()->isLeaf());

    delete dataset;
    delete Tree;
    return TR_PASS;
  }

  // TestResult DecisionTreeClassify(){

  //   BinaryDataset *dataset = new BinaryDataset("Datasets/dataset_in6.txt", 2);
  //   BinaryDecisionTree* Tree = new BinaryDecisionTree(dataset);
  //   double obs1 = 0.678;
  //   double obs2 = 0;
  //   double *obsptr;

  //   obsptr = &obs1;
  //   ASSERT_EQUALS(Tree->classify(obsptr),1);
  //   obsptr = &obs2;
  //   ASSERT_EQUALS(Tree->classify(obsptr),-1);

  //   delete dataset;
  //   delete Tree;

  //   return TR_PASS;
  // }

  TestResult DecisionTreeClassify(){

    BinaryDataset *dataset = new BinaryDataset("Datasets/dataset_in6.txt", 2);
    BinaryDecisionTree* Tree = new BinaryDecisionTree(dataset);
    double obs1[] = {0.515,0.912};
    double obs2[] = {0.257,0.427};

    ASSERT_EQUALS(Tree->classify(obs1),1);
    ASSERT_EQUALS(Tree->classify(obs2),-1);

    delete dataset;
    delete Tree;

    return TR_PASS;
  }

#endif /*ENABLE_DECISIONTREE_TESTS*/

// TestResult customTest(){

//   return TR_PASS;
// }

/*
This function collects up all the tests as a vector of function pointers. If you create your own
tests and want to be able to run them, make sure you add them to the `tests` vector here.
*/
vector<TestResult (*)()> generateTests() {
  vector<TestResult (*)()> tests;
  #ifdef ENABLE_TASK_TESTS
    tests.push_back(&BaseTest);
  #endif /*ENABLE_TASK_TESTS*/
  #ifdef ENABLE_NODE_TESTS
  tests.push_back(&NodeGetAndSet);
  tests.push_back(&NodeIsLeafBasic);
  #endif /*ENABLE_NODE_TESTS*/
  #ifdef ENABLE_DATASET_TESTS
    tests.push_back(&DatasetGetAndSet);
    tests.push_back(&DatasetSplitLOO);
    tests.push_back(&DatasetSplit);
    tests.push_back(&DatasetOptimalSplit);
  #endif /*ENABLE_DATASET_TESTS*/
  #ifdef ENABLE_DECISIONTREE_TESTS
    tests.push_back(&DecisionTreeGrow);
    tests.push_back(&DecisionTreeClassify);
  #endif /*ENABLE_DECISIONTREE_TESTS*/
  // tests.push_back(&customTest);

  return tests;
}

int main(int argc, char const* argv[]) {
  // If one or more test numbers are passed as command-line parameters, execute them
  vector<TestResult (*)()> tests_to_run = generateTests();
  unsigned int pass_count = 0;
  unsigned int fail_count = 0;
  unsigned int run_count = 0;
  if (argc > 1) {
    for (int i = 1; i < argc; ++i) {
      unsigned int test_num = atoi(argv[i]);
      if (test_num > tests_to_run.size()) {
        cout << "ERROR: unknown test case " << test_num << endl;
        continue;
      }
      // run the test
      ++run_count;
      TestResult result = tests_to_run[test_num]();
      if (result == TR_FAIL) {
        cout << "FAIL: Test " << test_num << " failed." << endl;
        ++fail_count;
        return 99;
      } else {
        cout << "PASS: Test " << test_num << " passed." << endl;
        ++pass_count;
        return 0;
      }
    }
  } else {
    // otherwise, run all tests
    // Make sure to update this section as you add more tests
    // Add the tests for the first task
    for (unsigned int t = 0; t < tests_to_run.size(); ++t) {
      ++run_count;
      TestResult result = tests_to_run[t]();
      if (result == TR_FAIL) {
        cout << "FAIL: Test " << t << " failed." << endl;
        ++fail_count;
      } else {
        cout << "PASS: Test " << t << " passed." << endl;
        ++pass_count;
      }
    }
  }
  cout << "\n-------------------------------------------------\n"
  << "Total Run: " << run_count << "\n"
  << "Total PASSED: " << pass_count << "\n"
  << "Total FAILED: " << fail_count << "\n"
  << "-------------------------------------------------\n" << endl;

  if(pass_count == tests_to_run.size()) std::cout << "UwU Senpai" << endl;

  // Return 0 if everything was ok
  return 0;
}
