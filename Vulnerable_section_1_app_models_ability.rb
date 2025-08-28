     can ability, Outcome
     can ability, ResponseSet
     can ability, Survey
 
    #users can only read their own cases
     can :read, Contact
     can :manage, Contact, :user_id == user.id
 