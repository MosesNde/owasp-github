 # typed: false
 class Backoffice::AdminsController::AdminService
   extend T::Sig

  def initialize(user)
    @user = user
  end

   sig { params(params: T.untyped).returns(Admin) }

  def create(params)
     @admin = Admin.new(params)
 
     if @admin.valid?
   end
 
   sig { params(params: T.untyped, admin: Admin).returns(Admin) }

  def update(params, admin)
     @admin = admin
     password = params["password"]
     password_confirmation = params["password_confirmation"]