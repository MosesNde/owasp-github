# typed: true
 class Backoffice::MembersController::MemberService
   extend T::Sig
 
  def initialize(user)
    @user = user
  end

   sig { params(params: T.untyped, member: Member).returns(Member) }
 
  def update(params, member)
     @member = T.let(member, T.nilable(Member))
 
     if @member.nil?