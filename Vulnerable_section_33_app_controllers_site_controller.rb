 # typed: true
 class SiteController < ApplicationController
   layout "site"
   after_action :track_action
 
   private
 
   def track_action