# typed: true
 class Backoffice::AdminsController::AdminService
   extend T::Sig
   sig { params(params: T.untyped).returns(Admin) }