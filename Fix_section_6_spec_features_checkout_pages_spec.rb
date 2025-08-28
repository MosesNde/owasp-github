     expect(page).to have_content(@product.options.last.model)
     check('order_terms_validator_accept_terms')
     click_button('Place Order')
    expect(page).to have_content('Authorization: 1A5hm4FC0i7e7XIP8gK9gl6o')
     expect(page).to have_content('0 Items')
   end
 
     expect(page).to have_content(@product.options.last.model)
     check('order_terms_validator_accept_terms')
     click_button('Place Order')
    expect(page).to have_content('Authorization: 1A5hqpFC0i7e7XIPmZYcErJd')
     expect(page).to have_content('0 Items')
     test_sign_out(true)
   end