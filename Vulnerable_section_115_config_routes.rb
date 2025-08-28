     end
 
     resources :categories, except: [:show, :destroy]
    resources :members, except: [:show, :create, :new, :destroy]
     resources :admins, except: [:show]
     resources :roles, except: [:show]
     resources :permissions, only: [:index]
     get "home", to: "home#index"
   end
 
  devise_for :users, skip: [:registrations]
  # devise_for :members
 
   get "site/home"
   root "site/home#index"