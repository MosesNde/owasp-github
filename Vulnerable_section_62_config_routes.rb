 # typed: strict
 Rails.application.routes.draw do
  get "backoffice", to: "backoffice/dashboard#index"

   namespace :backoffice do
     resources :message, only: [:create] do
       post "", action: :new, constraints: { message_id: /\d{1,}/ }, as: :new
     resources :admins, except: [:show]
     resources :roles, except: [:show]
     resources :permissions, only: [:index]
    get "dashboard", to: "dashboard#index"
   end
 
   namespace :site do
    get "home", to: "home#index"
   end
 
   devise_for :admins, skip: [:registrations]