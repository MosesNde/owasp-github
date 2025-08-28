 # typed: false
 class Backoffice::AdminsController::AdminService
   extend T::Sig
   sig { params(params: T.untyped).returns(Admin) }
  def self.create(params)
     @admin = Admin.new(params)
 
     if @admin.valid?
   end
 
   sig { params(params: T.untyped, admin: Admin).returns(Admin) }
  def self.update(params, admin)
     @admin = admin
     password = params["password"]
     password_confirmation = params["password_confirmation"]