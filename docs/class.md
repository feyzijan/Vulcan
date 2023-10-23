# Vulcan Class 



## Bank Agent 

    

## Capital Firm



## Capital Good


## Household Agent 



### Initialization

A block of code (just testing markdown)


```
void Household_Agent::Set_Firm_Owner(Firm_Agent* firm_ptr){
    firm_owner = true;
    owned_firm = firm_ptr;
    unemployed = false;
    owned_firm->Set_Owner(this);
}
```

A Table (testing markdown)

variable | type | meaning
:----------- |:-------------:| -----------:
firm_owner        | boolean        | does agent own a firm?
owned_firm        | pointer        | point to firm









