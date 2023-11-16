#ifndef SCOPEPROCESSOR_H
#define SCOPEPROCESSOR_H

#include <string>
#include <vector>

using namespace std;

class ScopeProcessor
{
    private:
    public:
        ScopeProcessor(int scopeIdentifier, string name){
            this -> scopeIdentifier = scopeIdentifier;
            this -> name = name;
            this -> scopeProcessors = new vector<ScopeProcessor*>;
        }
        ScopeProcessor(string name)
        {
            this-> name = name;
            this-> scopeProcessors = new vector<ScopeProcessor*>;
        }

        int subIdentifier = 0;
        int scopeIdentifier;
        string name;
        vector<ScopeProcessor*>* scopeProcessors;

        void addMethod(ScopeProcessor* methodScopeProcessor)
        {
            this -> subIdentifier++;
            methodScopeProcessor->scopeIdentifier = subIdentifier;
            scopeProcessors -> push_back(methodScopeProcessor);
        }

        void addVariable(string name)
        {
            this -> subIdentifier++;
            scopeProcessors -> push_back(new ScopeProcessor(this->subIdentifier, name));
        }

        int findVariableSubIdentifier(string variableName){
            for(auto scope : *scopeProcessors)
            {
                if(!scope->name.compare(variableName)){
                    return scope->scopeIdentifier;
                }
            }
            return -1;
        }
};
#endif
