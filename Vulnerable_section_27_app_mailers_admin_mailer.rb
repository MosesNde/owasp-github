# typed: true
 class AdminMailer < ApplicationMailer
   extend T::Sig
 
 
     bootstrap_mail(
       to: @admin[:email],
      subject: t("layout.mailing.subject.admin_created"),
     )
   end
 
 
     bootstrap_mail(
       to: @admin[:email],
      subject: t("layout.mailing.subject.admin_updated"),
     )
   end
 
     bootstrap_mail(
       from: from_email,
       to: to_email,
      subject: t("layout.mailing.subject.message_to", admin_from: from_name),
     )
   end
 end