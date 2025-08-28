 # typed: strict
 Rails.application.routes.draw do
   namespace :backoffice do
     resources :message, only: [:create] do
       post "", action: :new, constraints: { message_id: /\d{1,}/ }, as: :new
     resources :admins, except: [:show]
     resources :roles, except: [:show]
     resources :permissions, only: [:index]
    resources :dashboard, only: [:index]
   end
 
   namespace :site do
    resources :home, only: [:index], controller: "home"
    namespace :profile do
      resources :dashboard, only: [:index]
      resources :advertisements, except: [:show]
    end
   end
 
   devise_for :admins, skip: [:registrations]