     can ability, Outcome
     can ability, ResponseSet
     can ability, Survey
    can ability, CustomerSupportNetworkMember
 
    #users can only read the cases of others
     can :read, Contact
     can :manage, Contact, :user_id == user.id
 