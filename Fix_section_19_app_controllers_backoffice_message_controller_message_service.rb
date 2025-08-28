 class Backoffice::MessageController::MessageService
   extend T::Sig
 
  def initialize(user)
    @user = user
  end

   sig {
     params(from_name: T.untyped, from_email: T.untyped, to_name: T.untyped, to_email: T.untyped, message: T.untyped)
       .returns(OpenStruct)
   }

  def send_message(from_name, from_email, to_name, to_email, message)
     @errors = T.let([], T.nilable(T::Array[T.untyped]))
     @message_sent = T.let(OpenStruct.new(success: false, message: ""), T.nilable(OpenStruct))
 
   private
 
   sig { void }

  def simulate_error?
     raise_error = [1..10].sample % 2 == 0
     Rails.logger.debug "Should raise an error? #{raise_error ? "yes" : "no"}"
     if raise_error