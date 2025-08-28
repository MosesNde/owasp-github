     resources :permissions, only: [:index]
     resources :dashboard, only: [:index]
   end
  get "backoffice", to: "backoffice/dashboard#index"
  get "site/profile", to: "site/profile/dashboard#index"
 
   namespace :site do
     resources :advertisements, only: [:show] do
      member do
        get "comments/new", controller: "comments", action: "new"
        post "comments", controller: "comments", action: "create"
      end

       collection do
         get "search"
       end
     end
     resources :categories, param: :description do
       get "advertisements"
     end
    resources :home, only: [:index]
     namespace :profile do
       resources :dashboard, only: [:index]
       resources :advertisements, except: [:show]