# include "FamilyTree.hpp"

using namespace family;


Tree :: Tree(string name)
{
    this->name = name;
    this->father = NULL;
    this->mother = NULL;
    level = 0;
    findName = "";
}

bool Tree :: existsFather(Tree * t)
{
    if(t->father != NULL)
    {
        return false;
    }
    return true;
}

bool Tree :: existsMother(Tree * t)
{
    if(t->mother != NULL)
    {
        return false;
    }
    return true;
}

Tree &Tree :: addFather(string child, string father)
{
     if(this->name == child)
    {
        if(existsFather(this))
        {
        this->father = new Tree(father);
        return *this;
        }
       throw runtime_error("already have a father");
    }
    else if(this->father == NULL && this->mother == NULL)
    {

        return *this;
    }
    else if(this->mother == NULL)
    {
        this->father->addFather(child, father);
    }
    else if(this->father == NULL)
    {
        this->mother->addFather(child, father);
    }
    else
    {
        this->father->addFather(child, father);
        this->mother->addFather(child, father);
    } 
    return *this;
}


Tree &Tree :: addMother(string child, string mother)
{ 
    if(this->name == child)
    {
        if(existsMother(this))
        {
        this->mother = new Tree(mother);
        return *this;
        }
        throw runtime_error("already have a mother");
    }
    else if(this->father == NULL && this->mother == NULL)
    {
        return *this;
    }
    else if(this->mother == NULL)
    {
        this->father->addMother(child, mother);
    }
    else if(this->father == NULL)
    {
        this->mother->addMother(child, mother);
    }
    else
    {
        this->father->addMother(child, mother);
        this->mother->addMother(child, mother);
    }
    return *this;
}

string Tree :: relation(string name)
{
       int level = relationHelp(this, name, 1);
    string res = "";
    string great = "great-";

    switch (level)
    {
    case 0:
        res = "unrelated";
        break;
    case 1:
        res = "me"; 
        break;
    case 2:
        res = "father"; 
        break;
    case -2:
        res = "mother"; 
        break;
    case 3:
        res = "grandfather"; 
        break;
    case -3:
        res = "grandmother"; 
        break;
    
    default:
        string sign = "";
        if(level > 0)
        {
            sign += "grandfather";
        }
        else
        {
            sign += "grandmother";
            level *= -1;
        }
    
        while(level-- > 3)
        {
            res += great;
        }
        res += sign;
        break;
    }
    return res;
}

string Tree :: find(string name)
{
    if (name == "me")
    {
        return this->name;
    }
    if (name == "mother")
    {
        if (this->mother == NULL)
        {
            throw runtime_error("No such a mother");
        }        
        return this->mother->name;
    }
    if (name == "father")
    {
        if (this->father == NULL)
        {
            throw runtime_error("No such a father");
        }  
        return this->father->name;
    }
     if (name == "grandfather")
    {
        if (this->father->father != NULL)
        {
           return this->father->father->name;
        }
        else  if (this->mother->father != NULL)
        {
             return this->mother->father->name;
        }
        throw runtime_error("No such a grandfather");
    }
     if (name == "grandmother")
    {
         if (this->father->mother != NULL)
        {
           return this->father->mother->name;
        }
        else  if (this->mother->mother != NULL)
        {
          return this->mother->mother->name;
        }
        throw runtime_error("No such a grandmother");
    }
    else
    {
        int level = 3;
        string s = name;
        while ((s != "grandmother" ) && (s != "grandfather"))
        {
            s = s.substr(6,(s.length()-6));
            level++;
        }
        findHelp(this,s, level);
        if (findName == "")
        {
            throw runtime_error("No such a " + name);
        }
        return findName;
        
    }  
}

void Tree :: display()
{
     if(this != NULL)
    {
        this->father->display();
        cout << this->name << endl;
        this->mother->display();
    }
    return;

}

void Tree :: remove(string name)
{
    if(relation(name) == "unrelated")
    {
        throw runtime_error("This name is not exists");
    }
    removeFind(this, name);
    return;
}

void Tree :: del(Tree * t, int relation)
{
    if(t == NULL)
    {
    return;
    }
    
    del(t->father, relation);
    del(t->mother, relation);
    
    delete(t);
    relation > 0 ? 
    this->father = NULL :
    this->mother = NULL;
}

 void Tree :: removeFind(Tree * t, string name)
{
    if(t->name == name)
    {
        int rel = relationHelp(t, name, 1);
        del(t, rel);

        return;
    }

    else if(t->father != NULL && t->mother != NULL)
    {
        removeFind(t->father, name); 
        removeFind(t->mother, name);
    }

    else if(t->father != NULL)
    {
        removeFind(t->father, name); 
    }

    else if(t->mother != NULL)
    {
        removeFind(t->mother, name);
    }

}

int Tree :: relationHelp(Tree * T, string name, int level)
{
     if(T->father == NULL && T->mother == NULL)
   {
       return 0;
   }

   if(T->name == name)
   {
       return level;
   }

    if(T->father->name == name)
   {
       return level + 1;
   }

    if(T->mother->name == name)
   {
       return ((level + 1) * (-1));
   }

   int downlevel = relationHelp(T->father, name, level + 1);

    if(downlevel != 0)
    {
        return downlevel;
    }

    downlevel = relationHelp(T->mother, name, level + 1);

    return downlevel;
}


int Tree :: findHelp(Tree * T,string name, int level)
{
     if (T == NULL)
    {
        return -1;
    }
    
   if(T->father == NULL && T->mother == NULL)
   {
       return -1;
   }

   if(level == 2 )
   {
       if (name == "grandmother")
       {
           findName = T->mother->name;
       }
       else
       {
           findName = T->father->name;
       }       
       return level;
   }
   int downlevel = findHelp(T->father,name, level-1);

    if(downlevel > 0)
    {
        return downlevel;
    }

    downlevel =  findHelp(T->mother,name, level-1);

    return downlevel;
}

int main()
{
    Tree * t = new Tree("Ohad");
    t->addFather("Ohad","Tzvi");
    t->addMother("Ohad","Tzipi");
    t->addFather("Tzvi", "F-Tzvi");
    t->addMother("Tzvi", "M-Tzvi");
    t->addFather("F-Tzvi","F-F-Tzvi");
    t->addFather("F-F-Tzvi","F-F-F-Tzvi");

    t->display();
    t->remove("F-F-F-Tzvi");
    cout << "--------After Remove--------" << endl;
    t->display();
}