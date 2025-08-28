 
 # ==== Methods ====
 def user_url(username = session[:username])
   "#{base_url}#{SERVER_CONF[:prefix]}#{username}"
 end
 
   return session[:approvals].member?(trust_root)
 end
 
def is_authorized(identity_url, trust_root)
  return (session[:username] and (identity_url == user_url) and approved(trust_root))
 end
 
 def openid
   else
     session[:approvals] = [oidreq.trust_root]
   end
  oidresp = oidreq.answer(true, nil, identity)
  add_sreg(oidreq, oidresp, userinfo)
  add_pape(oidreq, oidresp)
   return render_response(oidresp)
 end
 