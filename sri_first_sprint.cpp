class FactNode {
	string name;	// name of a People. e.g. "Mark"
	unordered_map<string, unordered_set<string> relation;		// all relations of a people
																// e.g. {{"Father", {Peter"}}, {"Brother", {"John"}}}
																// means Father(Mark,Peter), Brother(Mark,John)
};

class KnowledgeBase {
	unordered_map<string, FactNode> graph;						// store people and their relations
public:
	insertFact();
	dropFact();
};

class RuleBase {
	unordered_map<string, vector<list<string>>> rules;			// each list<string> will be regard as a relationship chain
puclic:
	insertRule();
	dropRule();		// (note) if delete a rule, also delete all other rules depend on that
};

class SRI {
	KnowledgeBase knowledgebase;
	RuleBase rulebase;
	parseStringInput();			// parse input string
	parseStringOutput();		// parse output string

public:
	executeQuery(string input);		// calling parseStringInput() to parse string, call function of drop, insert
									// in Base classes to execute query
	load();			// load rules and facts
	dump();			// dump rules and facts
};

